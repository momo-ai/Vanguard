#include "LLVMtoVanguard.h"
#include "Function.h"
#include "Block.h"
#include "Instruction.h"
#include "Module.h"

namespace vanguard{
    
    LLVMtoVanguard* LLVMtoVanguard::singletonLLVMtoVanguard = 0;

    LLVMtoVanguard::LLVMtoVanguard(){
    }

    LLVMtoVanguard* LLVMtoVanguard::getInstance(){
        if (singletonLLVMtoVanguard == 0){
            singletonLLVMtoVanguard = new LLVMtoVanguard();
        }
        return singletonLLVMtoVanguard;
    }

    vanguard::Module* LLVMtoVanguard::translateModule(llvm::Module* module){
        if(!moduleMap[module]){
            moduleMap[module] = new Module(*module);
        }
        return moduleMap[module];
    }

    vanguard::Function* LLVMtoVanguard::translateFunction(llvm::Function* function){
        if(!functionMap[function]){
            functionMap[function] = new Function(*function);
        }
        return functionMap[function];
    }

    vanguard::Instruction* LLVMtoVanguard::translateInstruction(llvm::Instruction* instruction){
        if (!instructionMap[instruction]){
            instructionMap[instruction] = new Instruction(*instruction);
        }
        return instructionMap[instruction];
    }

    vanguard::Block* LLVMtoVanguard::translateBlock(llvm::BasicBlock* block){
        if (!blockMap[block]){
            blockMap[block] = new Block(*block);
        }
        return blockMap[block];
    }

}