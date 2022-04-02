//
// Created by Jon Stephens on 4/2/22.
//

#include "AAWrapper.h"

namespace vanguard {
    AAWrapper::AAWrapper(llvm::Pass &pass, llvm::Function &fn) : pass(pass), fn(fn), aa(nullptr) {}
    void AAWrapper::invalidate() {
        aa = nullptr;
    }
    llvm::AAResults *AAWrapper::request() {
        if(noAlias()) {
            return nullptr;
        }

        if(aa == nullptr) {
            aa = &pass.getAnalysis<llvm::AAResultsWrapperPass>(fn).getAAResults();
        }

        return aa;
    }

    bool AAWrapper::noAlias() {
        return fn.isDeclaration();
    }
}
