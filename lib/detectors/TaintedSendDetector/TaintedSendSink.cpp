//
// Created by Ben Mariano on 4/3/22.
//

#include "TaintedSendSink.h"
#include "llvm/Analysis/MemoryLocation.h"
#include "../../MemoryVal.h"

using namespace std;
using namespace llvm;

namespace TaintedSend {
    bool TaintedSendSink::isSink(const llvm::Function &fn) const {
        string fname = fn.getName().str();
        // TODO: Move to libBlockchain
        return fname.compare("call") == 0;
    }

    std::vector<std::pair<FunctionLocation, Val *>> TaintedSendSink::sinkValues(const llvm::Function &fn) const {
        vector<pair<FunctionLocation, Val *>> vals;
        Value *valueArg = fn.getArg(1);
        //return Val::functionOutputs(fn);
        if(valueArg->getType()->isPointerTy()) {
            vals.emplace_back(INPUT, new MemoryVal(MemoryLocation::getBeforeOrAfter(valueArg)));
        }

        return vals;
    }
}
