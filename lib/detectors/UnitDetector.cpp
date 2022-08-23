//
// Created by Jon Stephens on 8/12/22.
//

#include "UnitDetector.h"
#include <iostream>

namespace vanguard {
    void UnitDetector::detect(Program &prog) {
        for(auto unit : prog.units()) {
            detect(*unit);
        }
    }
}