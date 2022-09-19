//
// Created by Kostas Ferles on 9/16/22.
//

#ifndef VANGUARD_PUBLICCALLBACKSDETECTOR_H
#define VANGUARD_PUBLICCALLBACKSDETECTOR_H

#include <iostream>
#include <domain/libBlockchain/Blockchain.h>
#include <domain/libBlockchain/BlockchainModel.h>
#include <detectors/UniverseDetector.h>
#include <domain/libBlockchain/rust/near/NearModel.h>
#include <analysis/llvm-utils/LLVMUtils.h>

namespace vanguard {

    template <typename Domain>
    class PublicCallbacksDetector : public UniverseDetector<Domain> {
    public:

        using Function = typename Domain::Function;
        using Block = typename Domain::Block;
        using Instruction = typename Domain::Instruction;

        void detect(typename Domain::Universe &universe) override {
            for(auto contract : universe.contracts()) {
                for(auto fn : contract->functions()) {
                    process(fn);
                }
            }
        }

        void process(Function *fun) {
            for (auto instr : fun->instructions()) {
                if (auto callBack = isCallbackCall(instr)) {
                    if (callBack->visibility() == Visibility::PRIVATE)
                        continue;

                    llvm::SmallVector<Block *> doms;
                    auto currBB = instr->block();
                    analysis::LLVMUtils<Domain>::getPostDominatedBlocks(currBB, doms);

                    for (auto postDom : doms) {
                        for (auto postInstr : postDom->instructions()) {
                            // Skip instructions prior to the callback.
                            if (postDom == currBB && analysis::LLVMUtils<Domain>::postDominates(instr, postInstr))
                                continue;

                            if (auto postCall = dynamic_cast<CallIns<Domain>*>(postInstr)) {
                                // TODO: handle all APIs that register a callback

                                // TODO: maybe create a declared target method
                                auto trgs = postCall->targets();
                                if (std::any_of(trgs.begin(), trgs.end(),  [](auto trg) -> bool {
                                    return NearModel<Domain>::demangleRustName(*trg) == "near_sdk::promise::Promise::then";
                                }))
                                {
                                    publicCallbacks.insert(callBack);
                                }
                            }
                        }
                    }
                }
            }
        }

        Function * isCallbackCall(Instruction *inst) {
            if (auto callIns = dynamic_cast<CallIns<Domain> *>(inst)) {
                auto insFun = inst->block()->function();
                auto contract = insFun->contract();
                auto &model = contract->blockchainModel();
                auto contrFuns = contract->functions();

                if (model.isExternalCall(*callIns)) {

                    for (auto trg : callIns->targets()) {
                        auto matchesCallback = [&trg, this](Function *f) -> bool {
                            return rustFunctionNamesMatch(trg->name(),f->name());
                        };

                        auto it = std::find_if(contrFuns.begin(), contrFuns.end(), matchesCallback);

                        if (it != contrFuns.end()) return *it;
                    }
                }
            }

            return nullptr;
        }

        void report() override {
            for (auto pubCallback : publicCallbacks)
                std::cerr << "WARNING: Callback function " << pubCallback->name() << " has public visibility.\n";
        }

        static std::string name() {
            return "near-callbacks";
        }

        static Detector::DetectorDomain domain() {
            return Detector::BLOCKCHAIN;
        }

    private:

        std::set<Function*> publicCallbacks;

        bool rustFunctionNamesMatch(const std::string& fun1, const std::string& fun2) {
            auto name1 = fun1.substr(fun1.rfind(':') + 1);
            auto name2 = fun2.substr(fun2.rfind(':') + 1);
            return name1 == name2;
        }
    };
}

#endif //VANGUARD_PUBLICCALLBACKSDETECTOR_H
