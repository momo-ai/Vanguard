//
// Created by Jon Stephens on 8/12/22.
//

#ifndef VANGUARD_UNITDETECTOR_H
#define VANGUARD_UNITDETECTOR_H

#include "../program/LLVMtoVanguard.h"
#include <llvm/IR/PassManager.h>
#include <llvm/Passes/PassPlugin.h>

namespace vanguard {
    template <typename Detect> class UnitDetector : public llvm::PassInfoMixin<Detect> {
    public:
        virtual void detect(CompilationUnit &mod) = 0;

        static bool isRequired() { return true; }
        llvm::PreservedAnalyses run(llvm::Module &mod, llvm::ModuleAnalysisManager &modAnalysis) {
            auto &instance = LLVMtoVanguard::getInstance();
            detect(instance.translateModule(&mod));
            return llvm::PreservedAnalyses::all();
        }
    };
}



#endif //VANGUARD_UNITDETECTOR_H
