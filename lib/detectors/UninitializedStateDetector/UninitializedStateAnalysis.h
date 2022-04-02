//
// Created by Jon Stephens on 3/20/22.
//

#ifndef VANGUARD_UNINITIALIZEDSTATE_H
#define VANGUARD_UNINITIALIZEDSTATE_H

#include "../../Analysis.h"
#include <unordered_set>

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
        bool visited_constructor = false; // Track whether or not constructor has been visited
        string fname; // Current function name
        map<string, unordered_set<string>> uninitializedAccesses; // Tracks uninitialized accesses per function
        unordered_set<string> initializedVars; // Tracks variables which are globally initialized in constructor
        unordered_set<string> localInitializedVars; // Tracks variables which are locally initialized
        const blockchain::Blockchain *chain;
    };
}

#endif //VANGUARD_UNINITIALIZEDSTATE_H
