#include "Block.h"
#include "llvm/IR/CFG.h"
#include "LLVMtoVanguard.h"

namespace vanguard{

    Block::Block(const llvm::BasicBlock &blk): block(blk) {
    }

    Function* Block::getFunction(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateFunction(block.getParent());
    }

    std::list<Instruction*> Block::getInstructionsList(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Instruction*> instructions = {};
        for (auto &I : block){
            instructions.push_back(llvmToVanguard.translateInstruction(&I));
        }
        return instructions;
    }

    bool Block::isEntryBlock(){
        return block.isEntryBlock();
    }

    std::unordered_set< Block* > Block::getAllSuccessors(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::unordered_set<Block*> allSuccessors = {};
        for (auto *succ : llvm::successors(&block)) {
            allSuccessors.insert(llvmToVanguard.translateBlock(succ));
        }
        return allSuccessors;
    }

    llvm::BasicBlock* Block::unwrap(){
        return &block;
    }

}