#ifndef VANGUARD_PROGRAM_BLOCK_H
#define VANGUARD_PROGRAM_BLOCK_H

#include "Instruction.h"
#include <unordered_set>
#include <list>
#include "llvm/IR/BasicBlock.h"

namespace vanguard{
    class Block{
    public:
        explicit Block(const llvm::BasicBlock &block);

        Block(const Block&) = delete;

        std::string getName();

        Function* getFunction();

        std::list<Instruction *> getInstructionsList();

        bool isEntryBlock();

        std::unordered_set<Block *> getAllSuccessors();

        const llvm::BasicBlock& unwrap();

    private:
        const llvm::BasicBlock& block;

    };
}

#endif