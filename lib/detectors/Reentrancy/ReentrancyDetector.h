//
// Created by Jon Stephens on 9/3/22.
//

#ifndef VANGUARD_REENTRANCYDETECTOR_H
#define VANGUARD_REENTRANCYDETECTOR_H

#include <analysis/reachability/Reachable.h>
#include <domain/libBlockchain/BlockchainModel.h>
#include <detectors/UniverseDetector.h>
#include <iostream>
#include <unordered_map>

namespace vanguard {
    template <typename Domain>
    class ReentrancyDetector : public UniverseDetector<Domain> {
    public:
        using CompilationUnit = typename Domain::CompilationUnit;
        using Function = typename Domain::Function;
        using Block = typename Domain::Block;
        using Instruction = typename Domain::Instruction;

        struct CallTargetResolver : public InstructionClassVisitor<Domain> {
            typename Domain::Function *tgt = nullptr;
            void visit(const CallExpr<Domain> &v) override{
                tgt = v.target();
            }
        };

        struct StateModifiedReachability : public Reachable<Domain> {
            StateModifiedReachability(std::unordered_set<Function *>& writesStorage) : writesStorage(writesStorage) {};

            bool condition(Instruction &ins) {
                CallTargetResolver resolver;
                ins.accept(resolver);
                return ins.template writesStorage<Domain>() || writesStorage.find(resolver.tgt) != writesStorage.end();
            }

            std::unordered_set<Function *>& writesStorage;
        };

        void process(Function *fn) {
            processed.insert(fn);
            StateModifiedReachability reach(writesStorage);

            for(auto blk : fn->blocks()) {
                for(auto ins : blk->instructions()) {
                    CallTargetResolver resolver;
                    ins->accept(resolver);

                    if(resolver.tgt != nullptr && processed.find(resolver.tgt) == processed.end()) {
                        process(resolver.tgt);
                    }

                    if(ins->isAnyLowLevelCall() || writesStorage.find(resolver.tgt) != writesStorage.end()) {
                        writesStorage.insert(fn);
                        if(reach.reachable(*ins)) {
                            std::cout << "vulnerable" << std::endl;
                        }
                    }

                    if(ins->template writesStorage<Domain>() || writesStorage.find(resolver.tgt) != writesStorage.end()) {
                        calls.insert(fn);
                    }
                }
            }
        }

        void detect(Domain &universe) override {
            auto contracts = universe.template contracts<Domain>();
            for(auto contract : contracts) {
                for(auto fn : contract->functions()) {
                    process(fn);
                }
            }
        }

        virtual void report() override {
            std::cout << "Done!" << std::endl;
        }

        static std::string name() {
            return "Reentrancy";
        }

        static Detector::DetectorDomain domain() {
            return Detector::BLOCKCHAIN;
        }
    private:
        std::unordered_set<Function *> processed;
        std::unordered_set<Function *> writesStorage;
        std::unordered_set<Function *> calls;
    };
}


#endif //VANGUARD_REENTRANCYDETECTOR_H
