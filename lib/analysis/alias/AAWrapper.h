//
// Created by Jon Stephens on 8/22/22.
//

#ifndef VANGUARD_AAWRAPPER_H
#define VANGUARD_AAWRAPPER_H

#include "llvm/Analysis/AliasAnalysis.h"
#include <program/Base.h>

namespace vanguard {
    template<typename Domain>
    class AAWrapper {
    public:
        AAWrapper() : curFn(nullptr), fnAlias(nullptr) {}
        virtual llvm::AAResults *request(typename Domain::Function &reqFn) = 0;
        bool noAlias(typename Domain::Function &fn) {
            return fn.unwrap()->isDeclaration();
        }
    protected:
        typename Domain::Function *curFn;
        llvm::AAResults *fnAlias;
    };
}

#endif //VANGUARD_AAWRAPPER_H
