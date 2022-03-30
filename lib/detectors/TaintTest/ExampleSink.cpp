//
// Created by Jon Stephens on 3/30/22.
//

#include "ExampleSink.h"


namespace vanguard {
    bool ExampleSink::isSink(const llvm::Function &fn) {
        return true;
    }

    std::vector<Val *> ExampleSink::sinkValues(const llvm::Function &fn)  {
        // TODO: taint analysis does not take ownership of these values, they should be deleted here.
        return Val::functionOutputs(fn);
    }
}