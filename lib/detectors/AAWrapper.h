//
// Created by Jon Stephens on 8/22/22.
//

#ifndef VANGUARD_AAWRAPPER_H
#define VANGUARD_AAWRAPPER_H

#include "llvm/Analysis/AliasAnalysis.h"
#include "../program/Function.h"

namespace vanguard {
    class AAWrapper {
    public:
        AAWrapper();
        virtual llvm::AAResults *request(Function &reqFn) = 0;
        bool noAlias(Function &fn);
    protected:
        Function *curFn;
        llvm::AAResults *fnAlias;
    };
}

#endif //VANGUARD_AAWRAPPER_H
