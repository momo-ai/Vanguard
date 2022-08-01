#include "Instruction.h"
#include "Block.h"
#include "LLVMtoVanguard.h"
#include "llvm/IR/CFG.h"

namespace vanguard{
    Instruction::Instruction(llvm::Instruction &inst): instruction(inst) {
    }

    Block* Instruction::getBlock(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getSingletonLLVMtoVanguard();
        return llvmToVanguard->getVanguardBlock(instruction.getParent());
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
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getSingletonLLVMtoVanguard();
        return llvmToVanguard->getVanguardBlock(instruction.getSuccessor(n));
    }

    std::unordered_set<Block*> Instruction::getAllSuccessors(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getSingletonLLVMtoVanguard();
        std::unordered_set<Block*> allSuccessors = {};
        for (llvm::BasicBlock *Succ : llvm::successors(&instruction)) {
            allSuccessors.insert(llvmToVanguard->getVanguardBlock(Succ));
        }
        return allSuccessors;
    }

}