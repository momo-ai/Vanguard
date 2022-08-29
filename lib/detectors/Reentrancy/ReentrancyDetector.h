//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_ReentrancyEXAMPLE_H
#define VANGUARD_ReentrancyEXAMPLE_H

#include "../FunctionDetector.h"
//#import "../../Vanguard.cpp"
#include "../../domain/libBlockchain/include/Blockchain.h"
#include "../../program/InstructionClassVisitor.h"
#include "../../analysis/alias/AARequirement.h"

namespace vanguard {
    class ReentrancyDetector : public FunctionDetector, public vanguard::InstructionClassVisitor {
    public:
        explicit ReentrancyDetector(const std::string& summaryFile);
        bool shouldAnalyze(Function &fn);
        bool beginFn(Function &fn);
        bool transfer(Instruction &ins);
        bool endFn(Function &fn);
        std::string vulnerabilityReport();
        std::vector<Block *> findReachable(Block &blk, std::unordered_set<Block *> *exclude);

        // OG
        std::vector<Requirement *> registerAnalyses() override;
        void startDetection() override;
        bool detect(vanguard::Function &fn) override;
        void report() override;

        static std::string name();
        void visit(const CallExpr &v) override;

        static char ID;

    private:
        AARequirement *aa = nullptr;
        blockchain::Blockchain *chain = nullptr;
        // taken from ReentrancyAnalysis
        Function *lastExternalCall = nullptr; // Tracks last external call
        Function *curFn = nullptr; // Current function name
        std::map<Function *,Function *> potentialReentrancies; // Tracks potential reentrant funcs and external call
        std::map<Function *,std::tuple<bool,bool>> fnInfo; // Tracks for each func if it (1) has extern call or (2) has store
        bool modified = false; // Tracks if current function being analyzed has been updated in fnInfo on this pass
        std::string summary;
        // OG
//        ReentrancyAnalysis *analyzer;
    };
}


#endif //VANGUARD_ReentrancyEXAMPLE_H
