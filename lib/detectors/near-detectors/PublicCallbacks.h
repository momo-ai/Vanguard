//
// Created by Kostas Ferles on 9/8/22.
//

#ifndef VANGUARD_PUBLICCALLBACKS_H
#define VANGUARD_PUBLICCALLBACKS_H

#include <set>

#include "../../domain/libBlockchain/include/Near.h"
#include "../FunctionDetector.h"
#include "../../program/InstructionClassVisitor.h"
#include "../AARequirement.h"


namespace vanguard {
    class PublicCallbacks : public FunctionDetector {
    public:
        explicit PublicCallbacks(const std::string& summaryFile);

        std::vector<Requirement *> registerAnalyses() override;

        void startDetection() override;

        bool detect(vanguard::Function &fn) override;

        void report() override;

        static std::string name();

    private:
        // TODO: I think we should stop using AA directly.
        AARequirement *aa = nullptr;

        bool shouldAnalyze(Function &fn);

        std::set<blockchain::BlkFunction*> publicCallbacks;

        blockchain::Near *nearBlockChain;

        const std::string &summaryFile;

        blockchain::BlkFunction* isCallback(vanguard::Instruction *instr);
    };
}

#endif //VANGUARD_PUBLICCALLBACKS_H
