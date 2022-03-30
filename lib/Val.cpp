//
// Created by Jon Stephens on 3/29/22.
//

#include <llvm/IR/Instructions.h>
#include "Val.h"
#include "RegisterVal.h"
#include "llvm/IR/Type.h"

namespace vanguard {
    std::unordered_set<Val *> Val::functionOutputs(llvm::Function &fn) {
        std::unordered_set<Val *> outputs;

        if(fn.getReturnType() != llvm::Type::getVoidTy(fn.getContext())) {
            for(auto &blk : fn.getBasicBlockList()) {
                Instruction *blkTerm = blk.getTerminator();
                if (auto ret = llvm::dyn_cast<llvm::ReturnInst>(blkTerm)) {
                    for(auto &op : ret->operands()) {
                        Value *opVal = op.get();
                        if(auto ins = llvm::dyn_cast<llvm::Instruction>(opVal)) {
                            outputs.insert(new RegisterVal(*ins));
                        }
                    }
                }
            }
        }

        return outputs;
    }
}