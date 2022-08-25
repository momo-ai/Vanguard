//
// Created by Jon Stephens on 8/22/22.
//

#ifndef VANGUARD_REQUIREMENT_H
#define VANGUARD_REQUIREMENT_H

#include <llvm/IR/PassManager.h>

namespace vanguard {
    class Requirement {
    public:
        virtual void fetch(llvm::ModuleAnalysisManager &modAnalysis, llvm::Module &module) = 0;
    };
}

#endif //VANGUARD_REQUIREMENT_H
