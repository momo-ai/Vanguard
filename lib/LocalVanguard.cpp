//
// Created by Jon Stephens on 3/19/22.
//

#include "LocalVanguard.h"


namespace vanguard {
    bool LocalVanguard::runOnFunction(Function &fn) {
        runToFixedpoint(fn);
        return false;
    }

}