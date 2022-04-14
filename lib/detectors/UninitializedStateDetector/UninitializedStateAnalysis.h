//
// Created by Jon Stephens on 3/20/22.
//

#ifndef VANGUARD_UNINITIALIZEDSTATE_H
#define VANGUARD_UNINITIALIZEDSTATE_H

#include "../../Analysis.h"
#include <unordered_set>
#include <BlkVariable.h>
#include <BlkFunction.h>

using namespace vanguard;

namespace UninitializedState {
    class UninitializedStateAnalysis : public Analysis {
    public:
        UninitializedStateAnalysis(const blockchain::Blockchain *in_chain);
        bool shouldAnalyze(Function &fn) override;
        bool beginFn(Function &fn) override;
        bool transfer(Instruction &ins) override;
        bool endFn(Function &fn) override;
        string vulnerabilityReport() override;
    private:
        const blockchain::BlkFunction *curFn; // Current function name
        map<const blockchain::BlkFunction *, unordered_set<blockchain::BlkVariable *>> uninitializedAccesses; // Tracks uninitialized accesses per function
        unordered_set<blockchain::BlkVariable *> initializedVars; // Tracks variables which are globally initialized in constructor
        unordered_set<blockchain::BlkVariable *> localInitializedVars; // Tracks variables which are locally initialized
        const blockchain::Blockchain *chain;
    };
}

#endif //VANGUARD_UNINITIALIZEDSTATE_H
