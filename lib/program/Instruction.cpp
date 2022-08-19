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

    bool Instruction::isTerminator() {
        return instruction.isTerminator();
    }

    unsigned Instruction::getNumSuccessors(){
        if (instruction.isTerminator()) {
            return instruction.getNumSuccessors();
        }
        else {
            throw std::runtime_error("Instruction is not a terminator.");
        }
    }

    Block* Instruction::getSuccessor(unsigned n){
        if (instruction.isTerminator()) {
            if (n < instruction.getNumSuccessors()) {
                auto &llvmToVanguard = LLVMtoVanguard::getInstance();
                return llvmToVanguard.translateBlock(instruction.getSuccessor(n));
            } else {
                throw std::runtime_error("Argument to getSuccessor() is greater number of successors");
            }
        }
        else{
            throw std::runtime_error("Instruction is not a terminator.");
        }
        return nullptr;
    }

    std::unordered_set<Block*> Instruction::getAllSuccessors(){
        std::unordered_set<Block *> allSuccessors = {};
        if (instruction.isTerminator()) {
            int numSuccessors = instruction.getNumSuccessors();
            for (int i = 0; i < numSuccessors; i++) {
                allSuccessors.insert(this->getSuccessor(i));
            }
            return allSuccessors;
        }
        else{
            return allSuccessors;
        }
    }

    Value* Instruction::getOperand(unsigned i){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(instruction.getOperand(i));
    }

    unsigned Instruction::getNumOperands(){
        return instruction.getNumOperands();
    }

    const llvm::Instruction &Instruction::unwrap(){
        return instruction;
    }

}