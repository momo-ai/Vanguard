//
// Created by Jon Stephens on 3/19/22.
//

#include "SCCVanguard.h"
#include "llvm/Analysis/CallGraph.h"

namespace vanguard {
    bool SCCVanguard::runOnSCC(CallGraphSCC &scc) {
        for(auto node : scc) {
            Function *fn = node->getFunction();
            if(fn != nullptr) {
                runToFixedpoint(*fn);
            }
        }

        return false;
    }
}