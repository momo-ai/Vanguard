//
// Created by Jon Stephens on 8/12/22.
//

#ifndef VANGUARD_UNITDETECTOR_H
#define VANGUARD_UNITDETECTOR_H

#include "../program/LLVMtoVanguard.h"
#include <llvm/IR/PassManager.h>
#include <llvm/Passes/PassPlugin.h>
#include "ProgramDetector.h"

namespace vanguard {
    class UnitDetector : public ProgramDetector {
    public:
        virtual void detect(CompilationUnit &unit) = 0;
        void detect(Program &prog) override;
    };
}



#endif //VANGUARD_UNITDETECTOR_H
