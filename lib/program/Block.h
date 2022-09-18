#ifndef VANGUARD_BLOCK_H
#define VANGUARD_BLOCK_H

#include "Base.h"
#include "llvm/IR/CFG.h"

namespace vanguard{
    template<typename Domain>
    class Base<Domain>::Block {
    public:
        explicit Block(typename Domain::Factory &factory, const llvm::BasicBlock *blk): factory(factory), block(blk) {}
        Block(const Block&) = delete;
        virtual std::string name() {
            if (block->hasName()) {
                return block->getName().str();
            }
            else return "unnamed_block";
        }

        virtual bool isEntry() {
            return block->isEntryBlock();
        }

        virtual typename Domain::Function* function() const {
            return factory.createFn(block->getParent());
        }

        virtual const llvm::BasicBlock* unwrap() {
            return block;
        }

        virtual std::list<typename Domain::Instruction *> instructions() const {
            if(block == nullptr) {
                return {};
            }

            std::list<typename Domain::Instruction*> instructions = {};
            for (auto &I : *block){
                instructions.push_back(factory.createIns(&I));
            }
            return instructions;
        }

        virtual std::unordered_set<typename Domain::Block *> successors() const {
            std::unordered_set<Block*> allSuccessors = {};
            for (auto *succ : llvm::successors(block)) {
                allSuccessors.insert(factory.createBlk(succ));
            }
            return allSuccessors;
        }
    protected:
        const llvm::BasicBlock* block;
        typename Domain::Factory &factory;
    };

}

#endif