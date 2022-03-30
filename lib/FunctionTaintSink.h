//
// Created by Jon Stephens on 3/29/22.
//

#ifndef VANGUARD_FUNCTIONTAINTSINK_H
#define VANGUARD_FUNCTIONTAINTSINK_H


#include "TaintSink.h"
#include "llvm/IR/Function.h"
#include "Val.h"

namespace vanguard {
    class FunctionTaintSink : TaintSink {
    public:
        virtual bool isSink(const llvm::Function &fn) = 0;
        virtual std::vector<Val> sinkValues() = 0;
    private:
    };
}



#endif //VANGUARD_FUNCTIONTAINTSINK_H
