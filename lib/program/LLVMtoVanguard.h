#ifndef VANGUARD_PROGRAM_LLVMTOVANGUARD_H
#define VANGUARD_PROGRAM_LLVMTOVANGUARD_H

#include "CompilationUnit.h"
#include "Function.h"
#include "Instruction.h"
#include "Block.h"
//#include "Type.h"
//#include "Value.h"
#include <unordered_map>
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Value.h"

namespace vanguard{

    class LLVMtoVanguard{
        public:
            LLVMtoVanguard(const LLVMtoVanguard&) = delete;

            static LLVMtoVanguard& getInstance();
        
            CompilationUnit *translateModule(const llvm::Module *module);

            Function *translateFunction(const llvm::Function *function);

            Instruction *translateInstruction(const llvm::Instruction *instruction);

            Block *translateBlock(const llvm::BasicBlock *block);

            Type *translateType(const llvm::Type *t);

            Value *translateValue(const llvm::Value *val);

            InstructionVariable *translateInsVar(const llvm::Instruction *ins);

        private:
            static LLVMtoVanguard* singletonLLVMtoVanguard;
            LLVMtoVanguard();
            std::unordered_map<const llvm::Module*, CompilationUnit*> moduleMap;
            std::unordered_map<const llvm::Function*, Function*> functionMap;
            std::unordered_map<const llvm::BasicBlock*, Block*> blockMap;
            std::unordered_map<const llvm::Instruction*, Instruction*> instructionMap;
            std::unordered_map<const llvm::Type*, Type*> typeMap;
            std::unordered_map<const llvm::Value*, Value*> valueMap;

    };
}

#endif //VANGUARD_PROGRAM_LLVMTOVANGUARD_H
