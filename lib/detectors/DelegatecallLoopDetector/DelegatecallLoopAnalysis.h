//
// Created by Benjamin Mariano on 4/3/22.
//

#ifndef VANGUARD_MSGVALUEANALYSIS_H
#define VANGUARD_MSGVALUEANALYSIS_H


#include "../../Analysis.h"
#include <unordered_set>

using namespace vanguard;

namespace DelegatecallLoop {
    class DelegatecallLoopAnalysis : public Analysis {
    public:
        DelegatecallLoopAnalysis(const blockchain::Blockchain *in_chain);
        bool shouldAnalyze(Function &fn) override;
        bool beginFn(Function &fn) override;
        bool transfer(Instruction &ins) override;
        bool endFn(Function &fn) override;
        string vulnerabilityReport() override;
    private:
        unordered_set<string> loopWithDelegate; // Track loop bodies with call to delegate call
        unordered_set<string> funcsWithBadDelegate; // Track which functions have potential bad call to delegate
        string fname; // Current function name
        bool isPayable; // Whether or not current function is payable
        const blockchain::Blockchain *chain;
    };
}

#endif //VANGUARD_MSGVALUEANALYSIS_H
