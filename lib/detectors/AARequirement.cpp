//
// Created by Jon Stephens on 8/22/22.
//

#include "AARequirement.h"
#include <llvm/IR/PassManager.h>

namespace vanguard {
    llvm::AAResults *AARequirement::request(Function &reqFn) {
        if(noAlias(reqFn)) {
            return nullptr;
        }

        if(curFn == &reqFn) {
            return fnAlias;
        }

        curFn = &reqFn;
        auto *fn = const_cast<llvm::Function *>(&reqFn.unwrap());
        fnAlias = &fnAnalysis->getResult<llvm::AAManager>(*fn);

        return fnAlias;
    }

    void AARequirement::fetch(llvm::ModuleAnalysisManager &mam, llvm::FunctionAnalysisManager &fam) {
        fnAnalysis = &fam;
    }
};