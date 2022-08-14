//
// Created by Jon Stephens on 8/13/22.
//

#include "FunctionPrinter.h"
#include "../../Vanguard.h"

namespace vanguard {
    void FunctionPrinter::registerAnalyses() {}

    void FunctionPrinter::startDetection() {}

    void FunctionPrinter::detect(Function &fn) {
        auto &out = Vanguard::out();
        out << "Found Function: " << fn.getName() << "\n";
    }

    void FunctionPrinter::report() {
        auto &out = Vanguard::out();
        out << "Done!\n";
    }
}