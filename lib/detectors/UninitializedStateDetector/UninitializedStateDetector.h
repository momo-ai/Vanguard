//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_UNINITIALIZEDSTATEEXAMPLE_H
#define VANGUARD_UNINITIALIZEDSTATEEXAMPLE_H

#include "../../IntraproceduralVanguard.h"
#include "UninitializedStateAnalysis.h"

using namespace vanguard;

namespace UninitializedState {
    class UninitializedStateDetector : public IntraproceduralVanguard {
    public:
        static char ID;
        UninitializedStateDetector();
        ~UninitializedStateDetector();
    private:
        UninitializedStateAnalysis *analyzer;

    };
}


#endif //VANGUARD_UNINITIALIZEDSTATE_H
