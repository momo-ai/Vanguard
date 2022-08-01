#include "Block.h"
#include "llvm/IR/CFG.h"
#include "LLVMtoVanguard.h"

namespace vanguard{

    Block::Block(llvm::BasicBlock &blk): block(blk) {
    }

    const Function* Block::getFunction(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getSingletonLLVMtoVanguard();
        return llvmToVanguard->getVanguardFunction(block.getParent());
    }

    llvm::SymbolTableList< llvm::Instruction >* Block::getInstructionsList(){
        return &block.getInstList();
    }

    bool Block::isEntryBlock(){
        return block.isEntryBlock();
    }

    std::unordered_set< Block* > Block::getAllSuccessors(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getSingletonLLVMtoVanguard();
        std::unordered_set<Block*> allSuccessors = {};
        for (llvm::BasicBlock *Succ : llvm::successors(&block)) {
            allSuccessors.insert(llvmToVanguard->getVanguardBlock(Succ));
        }
        return allSuccessors;
    }

}