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

        std::string name();

        Function* parent();

        std::list<Instruction *> instructions();

        bool isEntry();

        std::unordered_set<Block *> successors();

        const llvm::BasicBlock& unwrap();

    private:
        const llvm::BasicBlock& block;

    };
}

#endif