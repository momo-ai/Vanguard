//
// Created by Kostas Ferles on 9/5/22.
//

#include "DARequirement.h"
#include <llvm/IR/PassManager.h>

namespace vanguard {
    llvm::DependenceInfo *DARequirement::request(Function &reqFn) {
        if (depInfo.find(&reqFn) == depInfo.end()){
            auto *fn = const_cast<llvm::Function *>(&reqFn.unwrap());
            depInfo[&reqFn] = &fnAnalysis->getResult<llvm::DependenceAnalysis>(*fn);
        }

        return depInfo[&reqFn];
    }

    void DARequirement::fetch(llvm::ModuleAnalysisManager &mam, llvm::FunctionAnalysisManager &fam) {
        fnAnalysis = &fam;
    }
}
