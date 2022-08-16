#include "Instruction.h"
#include "Block.h"
#include "LLVMtoVanguard.h"
#include "llvm/IR/CFG.h"

namespace vanguard{
    Instruction::Instruction(const llvm::Instruction &inst): instruction(inst) {
    }

    Block* Instruction::getBlock(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateBlock(instruction.getParent());
    }

    const char* Instruction::getInstructionType(){
        return instruction.getOpcodeName();
    }

    bool Instruction::mayReadOrWriteToMemory(){
        return instruction.mayReadOrWriteMemory();
    }

    bool Instruction::willReturn(){
        return instruction.willReturn();
    }

    unsigned Instruction::getNumSuccessors(){
        return instruction.getNumSuccessors();
    }

    Block* Instruction::getSuccessor(unsigned n){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateBlock(instruction.getSuccessor(n));
    }

    std::unordered_set<Block*> Instruction::getAllSuccessors(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::unordered_set<Block*> allSuccessors = {};
        for (auto *Succ : llvm::successors(&instruction)) {
            allSuccessors.insert(llvmToVanguard.translateBlock(Succ));
        }
        return allSuccessors;
    }

    Value* Instruction::getOperand(unsigned i){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(instruction.getOperand(i));
    }

    unsigned Instruction::getNumOperands(){
        return instruction.getNumOperands();
    }

    const llvm::Instruction* Instruction::unwrap(){
        return &instruction;
    }

}