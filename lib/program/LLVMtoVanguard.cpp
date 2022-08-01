#include "LLVMtoVanguard.h"
#include "Function.h"
#include "Block.h"
#include "Instruction.h"
#include "Module.h"

namespace vanguard{
    
    LLVMtoVanguard* LLVMtoVanguard::singletonLLVMtoVanguard = 0;

    LLVMtoVanguard::LLVMtoVanguard(){
    }

    LLVMtoVanguard* LLVMtoVanguard::getSingletonLLVMtoVanguard(){
        if (singletonLLVMtoVanguard == 0){
            singletonLLVMtoVanguard = new LLVMtoVanguard();
        }
        return singletonLLVMtoVanguard;
    }

    vanguard::Module* LLVMtoVanguard::getVanguardModule(llvm::Module* module){
        return moduleMap[module];
    }

    vanguard::Function* LLVMtoVanguard::getVanguardFunction(llvm::Function* function){
        return functionMap[function];
    }

    vanguard::Instruction* LLVMtoVanguard::getVanguardInstruction(llvm::Instruction* instruction){
        return instructionMap[instruction];
    }

    vanguard::Block* LLVMtoVanguard::getVanguardBlock(llvm::BasicBlock* block){
        return blockMap[block];
    }

}