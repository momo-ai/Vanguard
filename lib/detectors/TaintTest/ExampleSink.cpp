//
// Created by Jon Stephens on 3/30/22.
//

#include "ExampleSink.h"


namespace vanguard {
    bool ExampleSink::isSink(const llvm::Function &fn) const {
        return true;
    }

    std::vector<std::pair<FunctionLocation, Val *>> ExampleSink::sinkValues(const llvm::Function &fn) const {
        // TODO: taint analysis does not take ownership of these values, they should be deleted here.
        return Val::functionOutputs(fn);
    }
}