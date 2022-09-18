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

            std::list<Instruction*> instructions = {};
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
        //virtual std::list<typename Domain::Instruction *> insts() const ;
        //virtual std::unordered_set<typename Domain::Block *> succs() const;

        const llvm::BasicBlock* block;
        typename Domain::Factory &factory;
    };

    /*template<typename Domain>
    Universe<Domain>::Block::Block(Factory &factory, const llvm::BasicBlock *blk): factory(factory), block(blk) {}

    template<typename Domain>
    std::string Universe<Domain>::Block::name(){
        if (block->hasName()) {
            return block->getName().str();
        }
        else return "unnamed_block";
    }


    template<typename Domain>
    typename Domain::Function* Universe<Domain>::Block::function() const {
        return factory.createFn(block->getParent());
    }

    template<typename Domain>
    std::list<typename Domain::Instruction*> Universe<Domain>::Block::instructions() const{
        if(block == nullptr) {
            return {};
        }

        std::list<Instruction*> instructions = {};
        for (auto &I : *block){
            instructions.push_back(factory.createIns(&I));
        }
        return instructions;
    }

    template<typename Domain>
    bool Universe<Domain>::Block::isEntry(){
        return block->isEntryBlock();
    }

    template<typename Domain>
    std::unordered_set<typename Domain::Block* > Universe<Domain>::Block::successors() const{
        std::unordered_set<Block*> allSuccessors = {};
        for (auto *succ : llvm::successors(block)) {
            allSuccessors.insert(factory.createBlk(succ));
        }
        return allSuccessors;
    }

    template<typename Domain>
    const llvm::BasicBlock *Universe<Domain>::Block::unwrap(){
        return block;
    }*/

}

#endif