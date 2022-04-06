//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_ReentrancyEXAMPLE_H
#define VANGUARD_ReentrancyEXAMPLE_H

#include "../../IntraproceduralVanguard.h"
#include "ReentrancyAnalysis.h"

using namespace vanguard;

namespace Reentrancy {
    class ReentrancyDetector : public IntraproceduralVanguard {
    public:
        static char ID;
        ReentrancyDetector();
    private:
        ReentrancyAnalysis *analyzer;

    };
}


#endif //VANGUARD_Reentrancy_H
