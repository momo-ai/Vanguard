#ifndef VANGUARD_PROGRAM_BLOCK_H
#define VANGUARD_PROGRAM_BLOCK_H

#include "Instruction.h"
#include "Universe.h"
#include <unordered_set>
#include <list>
#include "llvm/IR/BasicBlock.h"

namespace vanguard{
    class Universe::Block{
    public:
        explicit Block(UnitFactory &factory, const llvm::BasicBlock &block);

        Block(const Block&) = delete;

        std::string name();

        Function* parent();

        std::list<Instruction *> instructions();

        bool isEntry();

        std::unordered_set<Block *> successors();

        const llvm::BasicBlock& unwrap();

    protected:
        const llvm::BasicBlock& block;
        UnitFactory &factory;
    };
}

#endif