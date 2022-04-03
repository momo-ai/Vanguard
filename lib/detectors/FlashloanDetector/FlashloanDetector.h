//
// Created by Jon Stephens on 3/30/22.
//

#ifndef VANGUARD_TAINTEXAMPLE_H
#define VANGUARD_TAINTEXAMPLE_H

#include "../../IntraproceduralVanguard.h"
#include "FlashloanAnalysis.h"

namespace flashloan {
    class FlashloanDetector : public vanguard::IntraproceduralVanguard {
    public:
        static char ID;
        FlashloanDetector();
    private:
    };
}



#endif //VANGUARD_TAINTEXAMPLE_H
