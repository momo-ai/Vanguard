//
// Created by Ben Mariano on 4/3/22.
//

#ifndef VANGUARD_TAINTEDSENDSINK_H
#define VANGUARD_TAINTEDSENDSINK_H

#include "../../FunctionTaintSink.h"

using namespace vanguard;

namespace TaintedSend {
    class TaintedSendSink : public FunctionTaintSink {
    public:
        bool isSink(const llvm::Function &fn) const override;
        std::vector<std::pair<FunctionLocation, Val *>> sinkValues(const llvm::Function &fn) const override;
    private:
    };
}



#endif //VANGUARD_TAINTEDSENDSINK_H
