//
// Created by Ben Mariano on 4/3/22.
//

#ifndef VANGUARD_TAINTEDSENDDETECTOR_H
#define VANGUARD_TAINTEDSENDDETECTOR_H

#include "../../IntraproceduralVanguard.h"
#include "TaintedSendAnalysis.h"

using namespace vanguard;

namespace TaintedSend {
    class TaintedSendDetector : public IntraproceduralVanguard {
    public:
        static char ID;
        TaintedSendDetector();
    private:
        TaintedSendAnalysis *analysis;
    };
}



#endif //VANGUARD_TAINTEDSENDDETECTOR_H
