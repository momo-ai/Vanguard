//
// Created by Jon Stephens on 8/13/22.
//

#include "FunctionPrinter.h"
#include <iostream>

namespace vanguard {
    void FunctionPrinter::detect(Function &fn) {
        std::cout << "Found Function: " << fn.getName() << std::endl;
    }
}