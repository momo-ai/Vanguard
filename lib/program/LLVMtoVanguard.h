#ifndef VANGUARD_PROGRAM_LLVMTOVANGUARD_H
#define VANGUARD_PROGRAM_LLVMTOVANGUARD_H

#include <unordered_map>
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instruction.h"


namespace vanguard{
    class Module;
    class Function;
    class Instruction;
    class Block;

    class LLVMtoVanguard{

        public:
            static vanguard::LLVMtoVanguard* getInstance();
        
            Module* translateModule(llvm::Module* module);

            Function* translateFunction(llvm::Function* function);

            Instruction* translateInstruction(llvm::Instruction* instruction);

            Block* translateBlock(llvm::BasicBlock* block);

        private:
            static LLVMtoVanguard* singletonLLVMtoVanguard;
            LLVMtoVanguard();
            std::unordered_map<llvm::Module*, Module*> moduleMap;
            std::unordered_map<llvm::Function*, Function*> functionMap;
            std::unordered_map<llvm::BasicBlock*, Block*> blockMap;
            std::unordered_map<llvm::Instruction*, Instruction*> instructionMap;

    };
}

#endif