#ifndef VANGUARD_PROGRAM_INSTRUCTION_H
#define VANGUARD_PROGRAM_INSTRUCTION_H

#include "Function.h"
#include <unordered_set>
#include "llvm/IR/Instruction.h"

namespace vanguard{

    class Instruction{
    public:
        Instruction(llvm::Instruction &inst);

        Block* getBlock();

        Function* getFunction();

        const char* getInstructionType();

        bool mayReadOrWriteToMemory();

        bool willReturn();

        unsigned getNumSuccessors();

        Block* getSuccessor(unsigned n);

        std::unordered_set<Block*> getAllSuccessors();

        Value* getOperand(unsigned i);

        unsigned getNumOperands();

        llvm::Instruction* unwrap();

    private:
        llvm::Instruction& instruction;
    };
}

#endif