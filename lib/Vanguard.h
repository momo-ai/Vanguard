//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_VANGUARD_H
#define VANGUARD_VANGUARD_H
#include "Analysis.h"

namespace vanguard {
    class Vanguard {
    protected:
        Analysis *analysis;

        virtual void registerAnalysis(Analysis *a);
    };
}
#endif //VANGUARD_VANGUARD_H
