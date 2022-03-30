//
// Created by Jon Stephens on 3/29/22.
//

#ifndef VANGUARD_FUNCTIONTAINTSOURCE_H
#define VANGUARD_FUNCTIONTAINTSOURCE_H

#include "TaintSource.h"
#include "llvm/IR/Function.h"
#include "Val.h"

namespace vanguard {
    /*
     * Create initial taint summary based off this information
     */
    class FunctionTaintSource : public TaintSource {
    public:
        virtual bool isSource(const llvm::Function &fn) = 0;
        virtual std::vector<Val *> sourceValues(const llvm::Function &fn) = 0;
    private:

    };
}



#endif //VANGUARD_FUNCTIONTAINTSOURCE_H
