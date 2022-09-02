#include "Block.h"
#include "llvm/IR/CFG.h"
#include "UnitFactory.h"

namespace vanguard{

    Universe::Block::Block(UnitFactory &factory, const llvm::BasicBlock &blk): factory(factory), block(blk) {}

    std::string Universe::Block::name(){
        if (block.hasName()) {
            return block.getName().str();
        }
        else return "unnamed_block";
    }


    Universe::Function* Universe::Block::parent(){
        return factory.createFn(block.getParent());
    }

    std::list<Universe::Instruction*> Universe::Block::instructions(){
        std::list<Instruction*> instructions = {};
        for (auto &I : block){
            instructions.push_back(factory.createIns(&I));
        }
        return instructions;
    }

    bool Universe::Block::isEntry(){
        return block.isEntryBlock();
    }

    std::unordered_set<Universe::Block* > Universe::Block::successors(){
        std::unordered_set<Block*> allSuccessors = {};
        for (auto *succ : llvm::successors(&block)) {
            allSuccessors.insert(factory.createBlk(succ));
        }
        return allSuccessors;
    }

    const llvm::BasicBlock &Universe::Block::unwrap(){
        return block;
    }

}