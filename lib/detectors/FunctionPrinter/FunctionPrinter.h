//
// Created by Jon Stephens on 8/13/22.
//

#ifndef VANGUARD_FUNCTIONPRINTER_H
#define VANGUARD_FUNCTIONPRINTER_H

#include "../IntraproceduralDetector.h"

namespace vanguard {
    class FunctionPrinter : public IntraproceduralDetector<FunctionPrinter> {
        void registerAnalyses() override;
        void startDetection() override;
        void detect(Function &fn) override;
        void report() override;
    };
}



#endif //VANGUARD_FUNCTIONPRINTER_H
