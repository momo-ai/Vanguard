//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_SCCEXAMPLE_H
#define VANGUARD_SCCEXAMPLE_H

#include "../../SCCVanguard.h"
#include "../../Taint.h"
#include "../../TaintAnalysis.h"

using namespace vanguard;

#include "ModPrint.h"

namespace sccexample {
    class SCCExample : public SCCVanguard{
    public:
        static char ID;
        SCCExample();
        ~SCCExample();
    private:
        ModPrint *printer;
    };
}



#endif //VANGUARD_SCCEXAMPLE_H
