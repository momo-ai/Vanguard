//
// Created by Benjamin Mariano on 4/3/22.
//

#ifndef VANGUARD_MSGVALUEANALYSIS_H
#define VANGUARD_MSGVALUEANALYSIS_H


#include "../../ReachAnalysis.h"
#include <unordered_set>

using namespace vanguard;

namespace MsgValueLoop {
    class MsgValueLoopAnalysis : public ReachAnalysis {
    public:
        MsgValueLoopAnalysis(const blockchain::Blockchain *in_chain);
        bool shouldAnalyze(Function &fn) override;
        bool beginFn(Function &fn) override;
        bool transfer(Instruction &ins) override;
        bool endFn(Function &fn) override;
        string vulnerabilityReport() override;
    private:
        unordered_set<const Function *> loopWithMsgValue; // Track loop bodies with ref to msg.value
        unordered_set<const Function *> funcsWithBadMsgValue; // Track which functions have potential bad msg.value accesses
        unordered_set<const Function *> fnsWithMsgValue;
        Function *curFn;
        const blockchain::Blockchain *chain;
    };
}

#endif //VANGUARD_MSGVALUEANALYSIS_H
