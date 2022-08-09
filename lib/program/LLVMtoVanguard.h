#ifndef VANGUARD_PROGRAM_LLVMTOVANGUARD_H
#define VANGUARD_PROGRAM_LLVMTOVANGUARD_H

#include "Module.h"
#include "Function.h"
#include "Instruction.h"
#include "Block.h"
#include "Type.h"
#include "Value.h"
#include <unordered_map>
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Value.h"


namespace vanguard{

    class LLVMtoVanguard{
        public:
            static vanguard::LLVMtoVanguard* getInstance();
        
            Module* translateModule(llvm::Module* module);

            Function* translateFunction(llvm::Function* function);

            Instruction* translateInstruction(llvm::Instruction* instruction);

            Block* translateBlock(llvm::BasicBlock* block);

            Type* translateType(llvm::Type &t);

            Value* translateValue(llvm::Value* t);

        private:
            static LLVMtoVanguard* singletonLLVMtoVanguard;
            LLVMtoVanguard();
            std::unordered_map<llvm::Module*, Module*> moduleMap;
            std::unordered_map<llvm::Function*, Function*> functionMap;
            std::unordered_map<llvm::BasicBlock*, Block*> blockMap;
            std::unordered_map<llvm::Instruction*, Instruction*> instructionMap;

            std::unordered_map<llvm::Type*, Type*> typeMap;
            std::unordered_map<llvm::Value*, Value*> valueMap;
    };
}

#endif