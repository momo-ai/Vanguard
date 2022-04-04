//
// Created by Jon Stephens on 3/29/22.
//

#ifndef VANGUARD_FUNCTIONTAINTSINK_H
#define VANGUARD_FUNCTIONTAINTSINK_H


#include "TaintSink.h"
#include "llvm/IR/Function.h"
#include "Val.h"
#include <unordered_set>

namespace vanguard {

    /*
     * Check associated function summary to see if appropriate location is tainted
     */
    class FunctionTaintSink : public TaintSink {
    public:
        FunctionTaintSink() = default;
        std::vector<TaintNode *> gatherTaint() override;
        //std::unordered_set<const llvm::Function *> generators();
        virtual bool isSink(const llvm::Function &fn) = 0;
        virtual std::vector<std::pair<FunctionLocation, Val *>> sinkValues(const llvm::Function &fn) = 0;
    private:
    };
}



#endif //VANGUARD_FUNCTIONTAINTSINK_H
