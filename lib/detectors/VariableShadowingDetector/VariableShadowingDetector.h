//
// Created by Jon Stephens on 4/3/22.
//

#ifndef VANGUARD_VARIABLESHADOWINGDETECTOR_H
#define VANGUARD_VARIABLESHADOWINGDETECTOR_H

#include "../../LocalVanguard.h"

namespace shadowing {
    class VariableShadowingDetector : public vanguard::LocalVanguard {
    public:
        static char ID;
        VariableShadowingDetector();
    };
}



#endif //VANGUARD_VARIABLESHADOWINGDETECTOR_H
