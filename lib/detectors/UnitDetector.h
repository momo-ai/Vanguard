//
// Created by Jon Stephens on 8/12/22.
//

#ifndef VANGUARD_UNITDETECTOR_H
#define VANGUARD_UNITDETECTOR_H

#include "../program/LLVMFactory.h"
#include <llvm/IR/PassManager.h>
#include <llvm/Passes/PassPlugin.h>
#include "UniverseDetector.h"

namespace vanguard {
    template<class Domain>
    class UnitDetector : public UniverseDetector<Domain> {
    public:
        virtual void detect(typename Domain::CompilationUnit &unit) = 0;
        void detect(Domain &universe) override {
            for(auto unit : universe.units()) {
                detect(*dynamic_cast<typename Domain::CompilationUnit *>(unit));
            }
        }
    };
}



#endif //VANGUARD_UNITDETECTOR_H
