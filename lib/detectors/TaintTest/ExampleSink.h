//
// Created by Jon Stephens on 3/30/22.
//

#ifndef VANGUARD_EXAMPLESINK_H
#define VANGUARD_EXAMPLESINK_H

#include "../../FunctionTaintSink.h"

namespace vanguard {
    class ExampleSink : public FunctionTaintSink {
    public:
        bool isSink(const llvm::Function &fn) override;
        std::vector<Val *> sinkValues(const llvm::Function &fn) override;
    private:
    };
}



#endif //VANGUARD_EXAMPLESINK_H
