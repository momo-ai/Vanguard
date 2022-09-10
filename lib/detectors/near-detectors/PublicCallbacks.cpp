//
// Created by Kostas Ferles on 9/8/22.
//

#include <iostream>

#include "PublicCallbacks.h"
#include "../../domain/libBlockchain/include/SummaryReader.h"
#include "../../analysis/llvm-utils/LLVMUtils.h"

namespace vanguard {
    PublicCallbacks::PublicCallbacks(const std::string &summaryFile) : summaryFile(summaryFile) {
        if(summaryFile.empty()) {
            throw runtime_error("Must provide a summary to the reentrancy detector");
        }
    }

    std::vector<Requirement *> PublicCallbacks::registerAnalyses() {
        aa = new AARequirement();
        std::vector<Requirement *> res = {aa};
        return res;
    }

    void PublicCallbacks::startDetection() {
        blockchain::SummaryReader sum = blockchain::SummaryReader(summaryFile, aa);
        nearBlockChain = (blockchain::Near*)sum.blockchain();
    }

    bool rustFunctionNamesMatch(const std::string& fun1, const std::string& fun2) {
        auto name1 = fun1.substr(fun1.rfind(':') + 1);
        auto name2 = fun2.substr(fun2.rfind(':') + 1);
        return name1 == name2;
    }

    blockchain::BlkFunction* PublicCallbacks::isCallback(vanguard::Instruction *instr) {
        if (auto callBack = dynamic_cast<vanguard::CallExpr *>(instr)) {
            Function *callBackFun = callBack->target();
            if (nearBlockChain->isAnyExternalCall(*callBackFun)) {
                auto blkFun = nearBlockChain->findFunction(*instr->parent()->parent());
                auto contract = (blockchain::BlkContract *) blkFun->parent();
                auto matchesCallback = [&callBackFun](const blockchain::BlkFunction *f) -> bool {
                    return rustFunctionNamesMatch(blockchain::Near::demangleRustName(*callBackFun),
                                                  f->blkName());
                };
                auto funs = contract->functions();

                auto it = std::find_if(funs.begin(), funs.end(), matchesCallback);
                return it == funs.end() ? nullptr : *it;
            }
        }

        return nullptr;
    }

    bool PublicCallbacks::detect(vanguard::Function &fn) {
        if (!shouldAnalyze(fn)) {
            return false;
        }

        for (auto instr : fn.instructions()) {
            if (auto callBack = isCallback(instr)) {
                if (callBack->visibility() == blockchain::Visibility::PRIVATE)
                    continue;

                llvm::SmallVector<vanguard::Block*> doms;
                auto currBB = (vanguard::Block*)instr->parent();
                analysis::LLVMUtils::getPostDominatedBlocks(currBB, doms);

                for (auto postDom : doms) {
                    for (auto postInstr : postDom->instructions()) {
                        // Skip instructions prior to the callback.
                        if (postDom == currBB && analysis::LLVMUtils::postDominates(instr, postInstr))
                            continue;

                        if (auto postCall = dynamic_cast<vanguard::CallExpr*>(postInstr)) {
                            // TODO: handle all APIs that register a callback
                            if (blockchain::Near::demangleRustName(*postCall->target()) == "near_sdk::promise::Promise::then"){
                                publicCallbacks.insert(callBack);
                            }
                        }
                    }
                }
            }
        }

        return false;
    }

    bool PublicCallbacks::shouldAnalyze(vanguard::Function &fn) {
        return nearBlockChain->isContractFunction(fn);
    }

    void PublicCallbacks::report() {
        for (auto pubCallback : publicCallbacks)
            cerr << "WARNING: Callback function " << pubCallback->blkName() << " has public visibility.\n";
    }

    string PublicCallbacks::name() {
        return "near-public-callbacks";
    }
}
