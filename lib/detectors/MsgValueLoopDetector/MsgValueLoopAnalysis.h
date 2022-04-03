//
// Created by Benjamin Mariano on 4/3/22.
//

#ifndef VANGUARD_MSGVALUEANALYSIS_H
#define VANGUARD_MSGVALUEANALYSIS_H


#include "../../Analysis.h"
#include <unordered_set>

using namespace vanguard;

namespace MsgValueLoop {
    class MsgValueLoopAnalysis : public Analysis {
    public:
        MsgValueLoopAnalysis(const blockchain::Blockchain *in_chain);
        bool shouldAnalyze(Function &fn) override;
        bool beginFn(Function &fn) override;
        bool transfer(Instruction &ins) override;
        bool endFn(Function &fn) override;
        string vulnerabilityReport() override;
    private:
        unordered_set<string> loopWithMsgValue; // Track loop bodies with ref to msg.value
        unordered_set<string> funcsWithBadMsgValue; // Track which functions have potential bad msg.value accesses
        string fname; // Current function name
        const blockchain::Blockchain *chain;
    };
}

#endif //VANGUARD_MSGVALUEANALYSIS_H
