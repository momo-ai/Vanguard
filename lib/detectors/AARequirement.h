//
// Created by Jon Stephens on 8/22/22.
//

#ifndef VANGUARD_AAREQUIREMENT_H
#define VANGUARD_AAREQUIREMENT_H


#include "Requirement.h"
#include "AAWrapper.h"

namespace vanguard {
    class AARequirement : public Requirement, public AAWrapper {
    public:
        virtual void fetch(llvm::ModuleAnalysisManager &modAnalysis, llvm::Module &module) override;
        llvm::AAResults *request(Function &reqFn) override;
    private:
        llvm::FunctionAnalysisManager *fnAnalysis;
    };
}



#endif //VANGUARD_AAREQUIREMENT_H
