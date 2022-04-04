//
// Created by Jon Stephens on 4/2/22.
//

#include "AAWrapper.h"

namespace vanguard {
    /*
     * TODO:I'm not sure why things keep breaking. Maybe swap this to be a singleton wrapper wrather than
     * having multiple wrappers and save the last alias analysis requested. If another fn requests, swap.
     */
    AAWrapper::AAWrapper(llvm::Pass &pass, llvm::Function &fn) : pass(pass), fn(fn), aa(nullptr) {}
    llvm::AAResults *AAWrapper::request() {
        if(noAlias()) {
            return nullptr;
        }

        return aa = &pass.getAnalysis<llvm::AAResultsWrapperPass>(fn).getAAResults();

        /*if(aa == nullptr) {
            aa = &pass.getAnalysis<llvm::AAResultsWrapperPass>(fn).getAAResults();
        }

        return aa;*/
    }

    bool AAWrapper::noAlias() {
        return fn.isDeclaration();
    }
}
