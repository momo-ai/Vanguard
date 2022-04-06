//
// Created by Benjamin Mariano on 4/3/22.
//

#ifndef VANGUARD_MSGVALUEDETECTOR_H
#define VANGUARD_MSGVALUEDETECTOR_H


#include "../../IntraproceduralVanguard.h"
#include "DelegatecallLoopAnalysis.h"

using namespace vanguard;

namespace DelegatecallLoop {
    class DelegatecallLoopDetector : public IntraproceduralVanguard {
    public:
        static char ID;
        DelegatecallLoopDetector();
    private:
        DelegatecallLoopAnalysis *analyzer;

    };
}


#endif //VANGUARD_MSGVALUEDETECTOR_H
