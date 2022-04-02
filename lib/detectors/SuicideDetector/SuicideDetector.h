//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_ReentrancyEXAMPLE_H
#define VANGUARD_ReentrancyEXAMPLE_H

#include "../../IntraproceduralVanguard.h"
#include "SuicideAnalysis.h"

using namespace vanguard;

namespace Suicide {
    class SuicideDetector : public IntraproceduralVanguard {
    public:
        static char ID;
        SuicideDetector();
        ~SuicideDetector();
    private:
        SuicideAnalysis *analyzer;
    };
}


#endif //VANGUARD_Suicide_H
