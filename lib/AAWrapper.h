//
// Created by Jon Stephens on 4/2/22.
//

#ifndef VANGUARD_AAWRAPPER_H
#define VANGUARD_AAWRAPPER_H

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Pass.h"

/*
 * Might eventually want to turn this into a requirement wrapper.
 */

namespace vanguard {
    class AAWrapper {
    public:
        AAWrapper(llvm::Pass &pass, llvm::Function &fn);
        llvm::AAResults *request();
        bool noAlias();
        //llvm::AAResults *alias();


    private:
        llvm::Pass &pass;
        llvm::Function &fn;
        llvm::AAResults *aa;
    };
}



#endif //VANGUARD_AAWRAPPER_H
