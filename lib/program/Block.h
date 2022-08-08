#ifndef VANGUARD_PROGRAM_BLOCK_H
#define VANGUARD_PROGRAM_BLOCK_H

#include "Instruction.h"
#include "LLVMtoVanguard.h"
#include <unordered_set>
#include <list>
#include "llvm/IR/BasicBlock.h"

namespace vanguard{
    class Block{
    public:
        Block(llvm::BasicBlock &block);

        const Function* getFunction();

        std::list<Instruction *> getInstructionsList();

        bool isEntryBlock();

        std::unordered_set<Block *> getAllSuccessors();

    private:
        llvm::BasicBlock& block;

    };
}

#endif