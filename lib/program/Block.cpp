#include "Universe.h"
#include "llvm/IR/CFG.h"
#include "UnitFactory.h"

namespace vanguard{

    Universe::Block::Block(UnitFactory &factory, const llvm::BasicBlock *blk): factory(factory), block(blk) {}

    std::string Universe::Block::name(){
        if (block->hasName()) {
            return block->getName().str();
        }
        else return "unnamed_block";
    }


    Universe::Function* Universe::Block::fn() const {
        return factory.createFn(block->getParent());
    }

    std::list<Universe::Instruction*> Universe::Block::insts() const{
        if(block == nullptr) {
            return {};
        }

        std::list<Instruction*> instructions = {};
        for (auto &I : *block){
            instructions.push_back(factory.createIns(&I));
        }
        return instructions;
    }

    bool Universe::Block::isEntry(){
        return block->isEntryBlock();
    }

    std::unordered_set<Universe::Block* > Universe::Block::succs() const{
        std::unordered_set<Block*> allSuccessors = {};
        for (auto *succ : llvm::successors(block)) {
            allSuccessors.insert(factory.createBlk(succ));
        }
        return allSuccessors;
    }

    const llvm::BasicBlock *Universe::Block::unwrap() const {
        return block;
    }

}