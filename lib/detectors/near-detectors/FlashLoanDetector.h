//
// Created by Kostas Ferles on 9/9/22.
//

#ifndef VANGUARD_FLASHLOANDETECTOR_H
#define VANGUARD_FLASHLOANDETECTOR_H

#include <set>

#include "../../domain/libBlockchain/include/Near.h"
#include "../FunctionDetector.h"
#include "../AARequirement.h"

namespace vanguard {

    class FlashLoanDetector : public FunctionDetector {
    public:
        explicit FlashLoanDetector(const std::string& summaryFile);

        std::vector<Requirement *> registerAnalyses() override;

        void startDetection() override;

        bool detect(vanguard::Function &fn) override;

        void report() override;

        static std::string name();

    // Private state.
    private:
        AARequirement *aa = nullptr;

        bool shouldAnalyze(Function &fn);

        std::set<blockchain::BlkFunction*> publicCallbacks;

        blockchain::Near *nearBlockChain;

        const std::string &summaryFile;

        std::map<vanguard::CallExpr*, std::set<vanguard::Instruction*>> warnings;

    // Private methods.
    private:
        bool dependsOnTotalBalance(vanguard::Instruction *instr, std::set<vanguard::Function*> &visited);

        bool dependsOnTotalBalance(vanguard::Function *fun, std::set<vanguard::Function*> &visited);

        void addWarning(vanguard::CallExpr* transferCall, vanguard::Instruction *totalBalance);

    // Private global state.
    private:
        static std::set<std::string> totalBalanceSignatures;

        static std::set<std::string> transferSignatures;
    };

}

#endif //VANGUARD_FLASHLOANDETECTOR_H
