//
// Created by Jon Stephens on 3/29/22.
//

#include <llvm/IR/Instructions.h>
#include "Val.h"
#include "RegisterVal.h"
#include "llvm/IR/Type.h"

namespace vanguard {
    ValType Val::getType() const {
        return type;
    }

    std::vector<Val *> Val::functionOutputs(const llvm::Function &fn) {
        std::vector<Val *> outputs;

        if(fn.getReturnType() != llvm::Type::getVoidTy(fn.getContext())) {
            for(auto &blk : fn) {
                const Instruction *blkTerm = blk.getTerminator();
                if (auto ret = llvm::dyn_cast<llvm::ReturnInst>(blkTerm)) {
                    for(auto &op : ret->operands()) {
                        Value *opVal = op.get();
                        outputs.push_back(new RegisterVal(*opVal));
                        //if(auto ins = llvm::dyn_cast<llvm::Instruction>(opVal)) {
                        //    outputs.insert(new RegisterVal(*ins));
                        //}
                    }
                }
            }
        }

        return outputs;
    }

    std::vector<Val *> Val::functionArgs(const llvm::Function &fn) {
        std::vector<Val *> args;

        for(auto &it : fn.args()) {
            args.push_back(new RegisterVal(it));
        }

        return args;
    }
}