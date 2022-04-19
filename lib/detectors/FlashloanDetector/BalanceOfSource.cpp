//
// Created by Jon Stephens on 3/30/22.
//

#include "BalanceOfSource.h"
#include "llvm/Analysis/MemoryLocation.h"
#include "../../MemoryVal.h"

using namespace vanguard;

using namespace vanguard;
using namespace llvm;
using namespace std;

namespace flashloan {
    bool BalanceOfSource::isSource(const llvm::Function &fn) {
        if(!fn.hasName()) {
            return false;
        }

        std::string fnName = fn.getName().str();
        return fnName.find("v__call_IERC20__function_balanceOf") != std::string::npos;
    }

    vector<pair<FunctionLocation, Val *>> BalanceOfSource::sourceValues(const llvm::Function &fn) {
        vector<pair<FunctionLocation, Val *>> vals;
        Value *retArg = fn.getArg(fn.arg_size() - 1);
        //return Val::functionOutputs(fn);
        if(retArg->getType()->isPointerTy()) {
            vals.emplace_back(OUTPUT, new MemoryVal(MemoryLocation::getAfter(retArg)));
        }

        return vals;
    }
}