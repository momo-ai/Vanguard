#include "LLVMtoVanguard.h"
#include "Function.h"
#include "Block.h"
#include "Instruction.h"
#include "Module.h"
#include "Type.h"

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

    Module* LLVMtoVanguard::translateModule(llvm::Module* module){
        if(!moduleMap[module]){
            moduleMap[module] = new Module(*module);
        }
        return moduleMap[module];
    }

    Function* LLVMtoVanguard::translateFunction(llvm::Function* function){
        if(!functionMap[function]){
            functionMap[function] = new Function(*function);
        }
        return functionMap[function];
    }

    Instruction* LLVMtoVanguard::translateInstruction(llvm::Instruction* instruction){
        if (!instructionMap[instruction]){
            instructionMap[instruction] = new Instruction(*instruction);
        }
        return instructionMap[instruction];
    }

    Block* LLVMtoVanguard::translateBlock(llvm::BasicBlock* block){
        if (!blockMap[block]){
            blockMap[block] = new Block(*block);
        }
        return blockMap[block];
    }

    Type* LLVMtoVanguard::translateType(llvm::Type& t){
        if (!typeMap[&t]){
            if (auto integer = llvm::dyn_cast<llvm::IntegerType>(&t)){
                typeMap[&t] = (llvm::dyn_cast<Type>(new IntegerT(*integer)));
            }
            else if (auto array = llvm::dyn_cast<llvm::ArrayType>(&t)){
                typeMap[&t] = (llvm::dyn_cast<Type>(new ArrayT(*array)));
            }
            // else if (auto function = llvm::dyn_cast<llvm::FunctionType>(&t)){
            //     typeMap[&t] = (llvm::dyn_cast<Type>(new FunctionT(*function)));
            // }
            else if (auto pointer = llvm::dyn_cast<llvm::PointerType>(&t)){
                typeMap[&t] = (llvm::dyn_cast<Type>(new PointerT(*pointer)));
            }
            else if (auto structT = llvm::dyn_cast<llvm::StructType>(&t)){
                typeMap[&t] = (llvm::dyn_cast<Type>(new StructT(*structT)));
            }
            else if (auto vector = llvm::dyn_cast<llvm::VectorType>(&t)){
                typeMap[&t] = (llvm::dyn_cast<Type>(new VectorT(*vector)));
            }
            else {
                throw std::runtime_error("Given type cannot be translated since it does not exist in vanguard yet.");
            }
        }
        return typeMap[&t];
    }

}