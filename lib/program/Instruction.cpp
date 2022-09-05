//
// Created by Jon Stephens on 8/26/22.
//

#include "Universe.h"
#include "Value.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include "LLVMFactory.h"
#include <string>
#include <list>
#include "InstructionClassVisitor.h"
#include "Block.h"
#include "Wrapped.h"

namespace vanguard {


    std::string Universe::Instruction::name() const {
        return ins->getName().str();
    }

    bool Universe::Instruction::willReturn() const {
        return ins->willReturn();
    }

    Value* Universe::Instruction::operandAt(unsigned i) const {
        return factory.createVal(ins->getOperand(i));
    }

    unsigned Universe::Instruction::numOperands() const {
        return ins->getNumOperands();
    }

    const llvm::Instruction &Universe::Instruction::unwrap() const {
        return *ins;
    }

    Universe::Block* Universe::Instruction::blk() const {
        return factory.createBlk(ins->getParent());
    }
}
