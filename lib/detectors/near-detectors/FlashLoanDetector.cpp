//
// Created by Kostas Ferles on 9/9/22.
//

#include <iostream>

#include "FlashLoanDetector.h"

#include "../../domain/libBlockchain/include/SummaryReader.h"
#include "../../analysis/llvm-utils/LLVMUtils.h"

namespace vanguard {

    // TODO: add more sources and eventually make this configurable.
    // TODO: make this a map whose key is a transfer function and value is a set of corresponding total balance functions.
    std::set<std::string> FlashLoanDetector::totalBalanceSignatures {"near_sdk::environment::env::account_balance"};

    // TODO: make this set complete.
    std::set<std::string> FlashLoanDetector::transferSignatures {"near_sdk::promise::Promise::transfer"};

    FlashLoanDetector::FlashLoanDetector(const std::string &summaryFile) : summaryFile(summaryFile) {
        if(summaryFile.empty()) {
            throw runtime_error("Must provide a summary to the reentrancy detector");
        }
    }

    std::vector<Requirement *> FlashLoanDetector::registerAnalyses() {
        aa = new AARequirement();
        std::vector<Requirement *> res = {aa};
        return res;
    }

    void FlashLoanDetector::startDetection() {
        blockchain::SummaryReader sum = blockchain::SummaryReader(summaryFile, aa);
        nearBlockChain = (blockchain::Near*)sum.blockchain();
    }

    bool FlashLoanDetector::shouldAnalyze(vanguard::Function &fn) {
        return nearBlockChain->isContractFunction(fn);
    }

    bool FlashLoanDetector::dependsOnTotalBalance(vanguard::Function *fun, std::set<vanguard::Function*> &visited){
        if (visited.find(fun) != visited.end())
            return false;

        visited.insert(fun);

        for (auto instr : fun->instructions()) {
            if (dependsOnTotalBalance(instr, visited))
                return analysis::LLVMUtils::returnDependsOnVal(fun, instr);
        }

        return false;
    }

    bool FlashLoanDetector::dependsOnTotalBalance(vanguard::Instruction *instr, std::set<vanguard::Function*> &visited) {

        if (auto call = dynamic_cast<vanguard::CallExpr*>(instr)) {
            auto trg = call->target();
            auto name = blockchain::Near::demangleRustName(*trg);

            if (totalBalanceSignatures.find(name) != totalBalanceSignatures.end())
                return true;

            if (shouldAnalyze(*trg) && dependsOnTotalBalance(trg, visited))
                return true;
        }

        return false;
    }

    bool FlashLoanDetector::detect(vanguard::Function &fn) {
        if (!shouldAnalyze(fn)) {
            return false;
        }

        for (auto instr: fn.instructions()) {
            if (auto callInstr = dynamic_cast<vanguard::CallExpr*>(instr)){
                auto trg = callInstr->target();

                // Skip llvm intrinsics.
                if (trg->name().find("llvm.") != std::string::npos)
                    continue;

                auto calledFuncName = blockchain::Near::demangleRustName(*trg);
                if (transferSignatures.find(calledFuncName) != transferSignatures.end()) {
                    // TODO: NEED TO GENERALIZE THE FOLLOWING LOGIC
                    auto transferArgs = callInstr->args();
                    auto valTransfered = transferArgs.back();
                    for (auto instr1 : fn.instructions()) {
                        std::set<Function*> visited;
                        if (analysis::LLVMUtils::valueDependsOn(valTransfered, instr1) && dependsOnTotalBalance(instr1, visited)) {
                            addWarning(callInstr, instr1);
                        }
                    }
                }
            }
        }

        return false;
    }

    void FlashLoanDetector::addWarning(vanguard::CallExpr* transferCall, vanguard::Instruction *totalBalanceInstr) {
        warnings[transferCall].insert(totalBalanceInstr);
    }

    void FlashLoanDetector::report() {
        for (const auto& warn : warnings) {
            auto transfer = warn.first;
            auto fun = transfer->parent()->parent();

            std::cerr << "WARNING: possible flashloan attack in " << blockchain::Near::demangleRustName(*fun)
                      << " (" << analysis::LLVMUtils::getLocInfo(fun).toStr() << ")" << ":\n";
            std::cerr << "    - Value transferred via " << blockchain::Near::demangleRustName(*transfer->target())
                      << " (" << analysis::LLVMUtils::getLocInfo(transfer).toStr()
                      << ") can be manipulated by the following locations:\n";
            for (auto &priceManipInstr : warn.second) {
                std::cerr << "        - " << analysis::LLVMUtils::getLocInfo(priceManipInstr).toStr() << "\n";
            }
            std::cerr << std::endl;
        }
    }

    std::string FlashLoanDetector::name() {
        return "near-flashloan";
    }
}