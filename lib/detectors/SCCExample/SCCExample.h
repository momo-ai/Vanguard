//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_SCCEXAMPLE_H
#define VANGUARD_SCCEXAMPLE_H

#include "../../SCCVanguard.h"
#include "../../Taint.h"
#include "../../TaintAnalysis.h"

using namespace vanguard;

namespace {
    class SCCExample : public SCCVanguard{
    public:
        static char ID;
        SCCExample();
    };
}



#endif //VANGUARD_SCCEXAMPLE_H
