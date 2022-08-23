//
// Created by Jon Stephens on 8/13/22.
//

#include "FunctionPrinter.h"
#include <iostream>

namespace vanguard {
    std::string FunctionPrinter::name() {
        return "fnPrinter";
    }

    void FunctionPrinter::registerAnalyses() {}

    void FunctionPrinter::startDetection() {}

    bool FunctionPrinter::detect(Function &fn) {
        std::cout << "Found Function: " << fn.getName() << std::endl;
        return false;
    }

    void FunctionPrinter::report() {
        std::cout << "Done!" << std::endl;
    }
}