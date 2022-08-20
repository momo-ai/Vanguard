//
// Created by Jon Stephens on 8/13/22.
//

#ifndef VANGUARD_INTERPROCEDURALDETECTOR_H
#define VANGUARD_INTERPROCEDURALDETECTOR_H

#include <unordered_set>
#include "UnitDetector.h"

namespace vanguard {
    class FunctionDetector : public UnitDetector {
    public:
        virtual bool detect(Function &fn) = 0;
        void detect(CompilationUnit &unit) override;
    };
}



#endif //VANGUARD_INTERPROCEDURALDETECTOR_H
