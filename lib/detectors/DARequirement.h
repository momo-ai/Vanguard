//
// Created by Kostas Ferles on 9/5/22.
//

#ifndef VANGUARD_DAREQUIREMENT_H
#define VANGUARD_DAREQUIREMENT_H

#include "Requirement.h"
#include "DAWrapper.h"

namespace vanguard {
    class DARequirement : public Requirement, public DAWrapper {
    public:
        virtual void fetch(llvm::ModuleAnalysisManager &mam, llvm::FunctionAnalysisManager &fam) override;

        llvm::DependenceInfo *request(Function &reqFn) override;

    private:
        llvm::FunctionAnalysisManager *fnAnalysis;
    };
}


#endif //VANGUARD_DAREQUIREMENT_H
