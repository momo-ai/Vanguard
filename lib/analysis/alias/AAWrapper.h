//
// Created by Jon Stephens on 8/22/22.
//

#ifndef VANGUARD_AAWRAPPER_H
#define VANGUARD_AAWRAPPER_H

#include "llvm/Analysis/AliasAnalysis.h"
#include "../../program/Function.h"

namespace vanguard {
    class AAWrapper {
    public:
        AAWrapper();
        virtual llvm::AAResults *request(Universe::Function &reqFn) = 0;
        bool noAlias(Universe::Function &fn);
    protected:
        Universe::Function *curFn;
        llvm::AAResults *fnAlias;
    };
}

#endif //VANGUARD_AAWRAPPER_H
