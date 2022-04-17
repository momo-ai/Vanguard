//
// Created by Jon Stephens on 3/20/22.
//

#ifndef VANGUARD_MODPRINT_H
#define VANGUARD_MODPRINT_H

#include "../../ReachAnalysis.h"

using namespace vanguard;

namespace Reentrancy {
    class ReentrancyAnalysis : public ReachAnalysis {
    public:
        ReentrancyAnalysis(const blockchain::Blockchain *in_chain);
        bool shouldAnalyze(Function &fn) override;
        bool beginFn(Function &fn) override;
        bool transfer(Instruction &ins) override;
        bool endFn(Function &fn) override;
        string vulnerabilityReport() override;
    private:
        Function *lastExternalCall = nullptr; // Tracks last external call
        Function *curFn; // Current function name
        map<Function *,Function *> potentialReentrancies; // Tracks potential reentrant funcs and external call
        map<Function *,tuple<bool,bool>> fnInfo; // Tracks for each func if it (1) has extern call or (2) has store
        bool modified; // Tracks if current function being analyzed has been updated in fnInfo on this pass
        const blockchain::Blockchain *chain;
    };
}

#endif //VANGUARD_MODPRINT_H
