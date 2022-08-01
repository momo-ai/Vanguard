#include "Block.h"
#include "llvm/IR/CFG.h"
#include "LLVMtoVanguard.h"

namespace vanguard{

    Block::Block(llvm::BasicBlock &blk): block(blk) {
    }

    const Function* Block::getFunction(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateFunction(block.getParent());
    }

    std::list<Instruction*> Block::getInstructionsList(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Instruction*> instructions = {};
        for (llvm::Instruction &I : block){
            instructions.push_back(llvmToVanguard->translateInstruction(&I));
        }
        return instructions;
    }

    bool Block::isEntryBlock(){
        return block.isEntryBlock();
    }

    std::unordered_set< Block* > Block::getAllSuccessors(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        std::unordered_set<Block*> allSuccessors = {};
        for (llvm::BasicBlock *Succ : llvm::successors(&block)) {
            allSuccessors.insert(llvmToVanguard->translateBlock(Succ));
        }
        return allSuccessors;
    }

}