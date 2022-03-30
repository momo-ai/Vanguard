//
// Created by Jon Stephens on 3/30/22.
//

#ifndef VANGUARD_EXAMPLESOURCE_H
#define VANGUARD_EXAMPLESOURCE_H

#include "../../FunctionTaintSource.h"

namespace vanguard {
    class ExampleSource : public FunctionTaintSource {
        bool isSource(const llvm::Function &fn) override;
        std::vector<Val *> sourceValues(const llvm::Function &fn) override;
    };
}



#endif //VANGUARD_EXAMPLESOURCE_H
