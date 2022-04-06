//
// Created by Benjamin Mariano on 4/3/22.
//

#ifndef VANGUARD_MSGVALUEDETECTOR_H
#define VANGUARD_MSGVALUEDETECTOR_H


#include "../../IntraproceduralVanguard.h"
#include "MsgValueLoopAnalysis.h"

using namespace vanguard;

namespace MsgValueLoop {
    class MsgValueLoopDetector : public IntraproceduralVanguard {
    public:
        static char ID;
        MsgValueLoopDetector();
    private:
        MsgValueLoopAnalysis *analyzer;

    };
}


#endif //VANGUARD_MSGVALUEDETECTOR_H
