//
// Created by Ben Mariano on 4/3/22.
//

#include "TaintedSendSource.h"
#include "llvm/Analysis/MemoryLocation.h"
#include "../../MemoryVal.h"

using namespace vanguard;
using namespace llvm;
using namespace std;

namespace TaintedSend {
    bool TaintedSendSource::isSource(const llvm::Function &fn) {
        string fname = fn.getName().str();
        // TODO: Move to libBlockchain
        return fname.compare("getCaller") == 0;
    }

    std::vector<std::pair<FunctionLocation, Val *>> TaintedSendSource::sourceValues(const llvm::Function &fn) {
        vector<std::pair<FunctionLocation, Val *>> vals;
        Value *retArg = fn.getArg(fn.arg_size() - 1);
        if(retArg->getType()->isPointerTy()) {
            vals.emplace_back(OUTPUT, new MemoryVal(MemoryLocation::getAfter(retArg)));
        }

        return vals;
    }
}
