#ifndef VANGUARD_PROGRAM_INSTRUCTION_H
#define VANGUARD_PROGRAM_INSTRUCTION_H

#include "Function.h"
#include <unordered_set>
#include "llvm/IR/Instruction.h"

namespace vanguard{

    class Instruction{
    private:
        const llvm::Instruction& instruction;

    public:
        explicit Instruction(const llvm::Instruction &inst);

        Instruction(const Instruction&) = delete;

        Block* getBlock();

        //Function* getFunction();

        const char* getInstructionType();

        bool mayReadOrWriteToMemory();

        bool willReturn();

        unsigned getNumSuccessors();

        Block* getSuccessor(unsigned n);

        std::unordered_set<Block*> getAllSuccessors();

    };
}

#endif