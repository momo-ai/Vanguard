//
// Created by Jon Stephens on 8/13/22.
//

#ifndef VANGUARD_INTRAPROCEDURALDETECTOR_H
#define VANGUARD_INTRAPROCEDURALDETECTOR_H

#include <llvm/IR/PassManager.h>
#include <llvm/Passes/PassPlugin.h>
#include "../program/LLVMtoVanguard.h"
#include "Detector.h"

namespace vanguard {
    template <typename Detect> class IntraproceduralDetector : public llvm::PassInfoMixin<Detect>, public Detector {
    public:
        IntraproceduralDetector() : started(false) {}

        virtual void detect(Function &fn) = 0;

        static bool isRequired() { return true; }
        llvm::PreservedAnalyses run(llvm::Function &fn, llvm::FunctionAnalysisManager &fnAnalysis) {
            if(!started) {
                registerAnalyses();
                startDetection();
            }
            auto &instance = LLVMtoVanguard::getInstance();
            detect(*instance.translateFunction(&fn));
            return llvm::PreservedAnalyses::all();
        }

    private:
        bool started;
    };
}


#endif //VANGUARD_INTRAPROCEDURALDETECTOR_H
