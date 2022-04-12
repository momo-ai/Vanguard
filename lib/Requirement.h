//
// Created by Jon Stephens on 4/11/22.
//

#ifndef VANGUARD_REQUIREMENT_H
#define VANGUARD_REQUIREMENT_H

#include "llvm/Pass.h"

namespace vanguard {
    class Requirement {
    public:
        virtual void registerRequirement(llvm::AnalysisUsage &info) const = 0;
    };
}



#endif //VANGUARD_REQUIREMENT_H
