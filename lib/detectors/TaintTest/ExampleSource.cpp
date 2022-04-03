//
// Created by Jon Stephens on 3/30/22.
//

#include "ExampleSource.h"


namespace vanguard {
    bool ExampleSource::isSource(const llvm::Function &fn) {
        return true;
    }

    std::vector<std::pair<FunctionLocation, Val *>> ExampleSource::sourceValues(const llvm::Function &fn) {
        // TODO: taint analysis does not take ownership of these values, they should be deleted here.
        return Val::functionArgs(fn);
    }
}