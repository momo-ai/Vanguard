//
// Created by Jon Stephens on 3/29/22.
//

#ifndef VANGUARD_FUNCTIONTAINTSOURCE_H
#define VANGUARD_FUNCTIONTAINTSOURCE_H

#include "TaintSource.h"
#include "llvm/IR/Function.h"
#include "Val.h"

namespace vanguard {
    class FunctionTaintSource : TaintSource {
    public:
        virtual bool isSource(const llvm::Function &fn) = 0;
        virtual std::vector<Val> sourceValues() = 0;
    private:
    };
}



#endif //VANGUARD_FUNCTIONTAINTSOURCE_H
