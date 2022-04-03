//
// Created by Jon Stephens on 3/29/22.
//

#include <llvm/IR/Instructions.h>
#include "Val.h"
#include "RegisterVal.h"
#include "llvm/IR/Type.h"
#include "unordered_map"
#include "llvm/Analysis/MemoryLocation.h"
#include "MemoryVal.h"

using namespace std;

namespace vanguard {
    ValType Val::getType() const {
        return type;
    }

    vector<pair<FunctionLocation, Val *>> Val::functionOutputs(const llvm::Function &fn) {
        vector<pair<FunctionLocation, Val *>> outputs;

        for(auto &arg : fn.args()) {
            if(arg.getType()->isPointerTy()) {
                //finding type size is annoying without call...
                outputs.emplace_back(OUTPUT, new MemoryVal((Value &) arg, 1));
            }
        }

        if(fn.getReturnType() != llvm::Type::getVoidTy(fn.getContext())) {
            for(auto &blk : fn) {
                const Instruction *blkTerm = blk.getTerminator();
                if (auto ret = llvm::dyn_cast<llvm::ReturnInst>(blkTerm)) {
                    for(auto &op : ret->operands()) {
                        Value *opVal = op.get();
                        outputs.emplace_back(OUTPUT, new RegisterVal(*opVal));
                    }
                }
            }
        }

        return outputs;
    }

    vector<pair<FunctionLocation, Val *>> Val::functionArgs(const llvm::Function &fn) {
        vector<pair<FunctionLocation, Val *>> args;

        for(auto &arg : fn.args()) {
            args.emplace_back(INPUT, new RegisterVal(arg));
            if(arg.getType()->isPointerTy()) {
                //finding type size is annoying without call...
                args.emplace_back(INPUT, new MemoryVal((Value &) arg, 1));
            }
        }

        return args;
    }

    std::unordered_map<Val *, Val *, ValPtrHash, ValPtrEq> Val::outVals(const CallInst &call) {
        const Function *caller = call.getFunction();
        const Function *callee = call.getCalledFunction();

        std::unordered_map<Val *, Val *, ValPtrHash, ValPtrEq> outVals;

        for(int i = 0; i < callee->arg_size(); ++i) {
            auto arg = callee->getArg(i);
            if(arg->getType()->isPointerTy()) {
                //just using this to figure out size. Currently not sure
                MemoryLocation argLoc = llvm::MemoryLocation::getForArgument((const CallBase *) &call, i, nullptr);
                MemoryLocation callerLoc = MemoryLocation(call.getOperand(i), argLoc.Size);
                MemoryLocation calleeLoc = MemoryLocation(arg, argLoc.Size);
                auto callerVal = new MemoryVal(callerLoc);
                auto calleeVal = new MemoryVal(calleeLoc);
                outVals[calleeVal] = callerVal;
            }
        }

        if(callee->getReturnType() != llvm::Type::getVoidTy(callee->getContext())) {
            for(auto &blk : *callee) {
                const Instruction *blkTerm = blk.getTerminator();
                if (auto ret = llvm::dyn_cast<llvm::ReturnInst>(blkTerm)) {
                    for(auto &op : ret->operands()) {
                        Value *opVal = op.get();
                        //outputs.push_back(new RegisterVal(*opVal));
                        outVals[new RegisterVal((Value &) *opVal)] = new RegisterVal((Value &) call);
                        if(opVal->getType()->isPointerTy()) {
                            MemoryLocation calleeLoc = llvm::MemoryLocation::getBeforeOrAfter(opVal);
                            //MemoryLocation callerLoc = llvm::MemoryLocation::getBeforeOrAfter(&call);
                            auto callerLoc = MemoryLocation(&call, calleeLoc.Size);
                            //MemoryLocation calleeLoc = MemoryLocation(opVal, callerLoc.Size);
                            /*if(!callMem.hasValue()) {
                                throw std::runtime_error("could not get returned memory");
                            }

                            MemoryLocation callerLoc = callMem.getValue();
                            MemoryLocation calleeLoc = MemoryLocation(opVal, callerLoc.Size);*/
                            auto callerVal = new MemoryVal(callerLoc);
                            auto calleeVal = new MemoryVal(calleeLoc);
                            outVals[calleeVal] = callerVal;
                        }
                    }
                }
            }
        }

        return outVals;
    }

    std::unordered_map<Val *, Val *, ValPtrHash, ValPtrEq> Val::inVals(const CallInst &call) {
        const Function *caller = call.getFunction();
        const Function *callee = call.getCalledFunction();

        std::unordered_map<Val *, Val *, ValPtrHash, ValPtrEq> inVals;

        for(int i = 0; i < callee->arg_size(); ++i) {
            auto calleeArg = callee->getArg(i);
            auto callerArg = call.getOperand(i);

            auto calleeReg = new RegisterVal(*calleeArg);
            auto callerReg = new RegisterVal(*callerArg);
            inVals[callerReg] = calleeReg;

            if(calleeArg->getType()->isPointerTy()) {
                //just using this to figure out size. Currently not sure
                MemoryLocation argLoc = llvm::MemoryLocation::getForArgument((const CallBase *) &call, i, nullptr);
                MemoryLocation callerLoc = MemoryLocation(callerArg, argLoc.Size);
                MemoryLocation calleeLoc = MemoryLocation(calleeArg, argLoc.Size);
                auto callerVal = new MemoryVal(callerLoc);
                auto calleeVal = new MemoryVal(calleeLoc);
                inVals[callerVal] = calleeVal;
            }
        }

        return inVals;
    }
}