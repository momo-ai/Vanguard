//
// Created by Jon Stephens on 8/12/22.
//

#include "UnitDetector.h"
#include <iostream>

namespace vanguard {
    void UnitDetector::detect(Universe &universe) {
        for(auto unit : universe.units()) {
            detect(*unit);
        }
    }
}