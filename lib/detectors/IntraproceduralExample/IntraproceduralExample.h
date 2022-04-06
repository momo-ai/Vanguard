//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_INTRAPROCEDURALEXAMPLE_H
#define VANGUARD_INTRAPROCEDURALEXAMPLE_H

#include "../../IntraproceduralVanguard.h"
#include "ModPrint.h"

using namespace vanguard;

namespace IntraExample {
    class IntraproceduralExample : public IntraproceduralVanguard {
    public:
        static char ID;
        IntraproceduralExample();
    private:
        ModPrint *printer;
    };
}


#endif //VANGUARD_INTRAPROCEDURALEXAMPLE_H
