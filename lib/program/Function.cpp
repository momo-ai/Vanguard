#include "Function.h"
#include "Block.h"
#include "LLVMtoVanguard.h"
#include "llvm/IR/InstIterator.h"

namespace vanguard{
    
    Function::Function(llvm::Function& func): function(func){
    }

    std::string Function::getName(){
        return function.getName().str();
    }

    bool Function::getParams(){
        return false;
    }

    Type* Function::getReturnType(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateType(*function.getReturnType());
    }

    bool Function::hasBody(){
        return true;
    }

    Block* Function::getBody(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateBlock(&function.getEntryBlock());
    }

    std::list<Instruction*> Function::getInstructionsList(){
        std::list<Instruction*> instrctionsList = {};
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        for (llvm::inst_iterator I = llvm::inst_begin(function), E = llvm::inst_end(function); I != E; ++I){
            instrctionsList.push_back(llvmToVanguard->translateInstruction(&*I));
        }
        return instrctionsList;
    }

    llvm::Function* Function::unwrap(){
        return &function;
    }

}