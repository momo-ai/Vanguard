//
// Created by Jon Stephens on 8/22/22.
//

#include "AAWrapper.h"

#include "AAWrapper.h"
#include "llvm/Analysis/AliasAnalysis.h"

namespace vanguard {
    AAWrapper::AAWrapper() : curFn(nullptr), fnAlias(nullptr) {}


    bool AAWrapper::noAlias(Function &fn) {
        return fn.unwrap().isDeclaration();
    }
}