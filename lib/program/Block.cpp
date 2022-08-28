#include "Block.h"
#include "llvm/IR/CFG.h"
#include "LLVMtoVanguard.h"

namespace vanguard{

    Block::Block(const llvm::BasicBlock &blk): block(blk) {
    }

    std::string Block::name(){
        if (block.hasName()) {
            return block.getName().str();
        }
        else return "unnamed_block";
    }


    Function* Block::parent(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateFunction(block.getParent());
    }

    std::list<Instruction*> Block::instructions(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Instruction*> instructions = {};
        for (auto &I : block){
            instructions.push_back(llvmToVanguard.translateInstruction(&I));
        }
        return instructions;
    }

    bool Block::isEntry(){
        return block.isEntryBlock();
    }

    std::unordered_set< Block* > Block::successors(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::unordered_set<Block*> allSuccessors = {};
        for (auto *succ : llvm::successors(&block)) {
            allSuccessors.insert(llvmToVanguard.translateBlock(succ));
        }
        return allSuccessors;
    }

    const llvm::BasicBlock &Block::unwrap(){
        return block;
    }

}