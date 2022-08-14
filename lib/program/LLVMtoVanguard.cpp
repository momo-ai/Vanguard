#include "LLVMtoVanguard.h"
#include "Function.h"
#include "Block.h"
#include "Instruction.h"
#include "CompilationUnit.h"
#include "Type.h"

namespace vanguard{
    
    LLVMtoVanguard* LLVMtoVanguard::singletonLLVMtoVanguard = 0;

    LLVMtoVanguard::LLVMtoVanguard(){
    }

    LLVMtoVanguard& LLVMtoVanguard::getInstance(){
        if (singletonLLVMtoVanguard == 0){
            singletonLLVMtoVanguard = new LLVMtoVanguard();
        }
        return *singletonLLVMtoVanguard;
    }

    CompilationUnit* LLVMtoVanguard::translateModule(const llvm::Module* module) {
        if(module == nullptr) {
            return nullptr;
        }

        if(!moduleMap[module]){
            moduleMap[module] = new CompilationUnit(*module);
        }
        return moduleMap[module];
    }

    Function* LLVMtoVanguard::translateFunction(const llvm::Function* fn) {
        if(fn == nullptr) {
            return nullptr;
        }

        if(!functionMap[fn]){
            functionMap[fn] = new Function(*fn);
        }
        return functionMap[fn];
    }

    Instruction* LLVMtoVanguard::translateInstruction(const llvm::Instruction* ins) {
        if(ins == nullptr) {
            return nullptr;
        }

        if (!instructionMap[ins]){
            instructionMap[ins] = new Instruction(*ins);
        }
        return instructionMap[ins];
    }

    Block* LLVMtoVanguard::translateBlock(const llvm::BasicBlock* block){
        if(block == nullptr) {
            return nullptr;
        }

        if (!blockMap[block]){
            blockMap[block] = new Block(*block);
        }
        return blockMap[block];
    }

    Type* LLVMtoVanguard::translateType(const llvm::Type* t){
        if(t == nullptr) {
            return nullptr;
        }

        if (!typeMap[t]){
            if (auto integer = llvm::dyn_cast<llvm::IntegerType>(t)){
                typeMap[t] = (llvm::dyn_cast<Type>(new IntegerType(*integer)));
            }
            else if (auto array = llvm::dyn_cast<llvm::ArrayType>(t)){
                typeMap[t] = (llvm::dyn_cast<Type>(new ArrayType(*array)));
            }
            // else if (auto function = llvm::dyn_cast<llvm::FunctionType>(&t)){
            //     typeMap[&t] = (llvm::dyn_cast<Type>(new FunctionT(*function)));
            // }
            else if (auto pointer = llvm::dyn_cast<llvm::PointerType>(t)){
                typeMap[t] = (llvm::dyn_cast<Type>(new PointerType(*pointer)));
            }
            else if (auto structT = llvm::dyn_cast<llvm::StructType>(t)){
                typeMap[t] = (llvm::dyn_cast<Type>(new StructType(*structT)));
            }
            else if (auto vector = llvm::dyn_cast<llvm::VectorType>(t)){
                typeMap[t] = (llvm::dyn_cast<Type>(new VectorType(*vector)));
            }
            else {
                throw std::runtime_error("Given type cannot be translated since it does not exist in vanguard yet.");
            }
        }
        return typeMap[t];
    }

}