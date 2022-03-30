//
// Created by Jon Stephens on 3/30/22.
//

#ifndef VANGUARD_TAINTEXAMPLE_H
#define VANGUARD_TAINTEXAMPLE_H

#include "../../IntraproceduralVanguard.h"
#include "AnalysisExample.h"

namespace vanguard {
    class TaintExample : public IntraproceduralVanguard {
    public:
        static char ID;
        TaintExample();
    private:
        AnalysisExample *analysis;
    };
}



#endif //VANGUARD_TAINTEXAMPLE_H
