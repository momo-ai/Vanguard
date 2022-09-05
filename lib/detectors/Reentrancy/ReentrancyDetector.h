//
// Created by Jon Stephens on 9/3/22.
//

#ifndef VANGUARD_REENTRANCYDETECTOR_H
#define VANGUARD_REENTRANCYDETECTOR_H

#include <detectors/UniverseDetector.h>
#include <iostream>

namespace vanguard {
    template <typename Domain>
    class ReentrancyDetector : public UniverseDetector<Domain> {
    public:
        using CompilationUnit = typename Domain::CompilationUnit;
        using Function = typename Domain::Function;
        using Block = typename Domain::Block;
        using Instruction = typename Domain::Instruction;


        virtual std::vector<Requirement *> registerAnalyses() override {
            return {};
        }

        virtual void startDetection() override {}

        virtual void detect(Domain &universe) override {
            auto contracts = universe.template contracts<Domain>();
            for(auto contract : contracts) {
                std::cout << "Found " << contract->name() << std::endl;
                for(auto fn : contract->functions()) {
                    std::cout << "  Has Function " << fn->name() << std::endl;

                    for(auto blk : fn->blocks()) {
                        for(auto ins : blk->instructions()) {
                            if(ins->isAnyLowLevelCall()) {
                                std::cout << "    Found a call" << std::endl;
                            }
                            else {
                                std::cout << "    Not a call" << std::endl;
                            }
                        }
                    }
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
    };
}


#endif //VANGUARD_REENTRANCYDETECTOR_H
