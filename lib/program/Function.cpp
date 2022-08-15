#include "Function.h"
#include "Block.h"
#include "LLVMtoVanguard.h"
#include "llvm/IR/InstIterator.h"

namespace vanguard{
    
    Function::Function(const llvm::Function& func): function(func){
    }

    std::string Function::getName(){
        return function.getName().str();
    }

    bool Function::getParams(){
        return false;
    }

    Type* Function::getReturnType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(function.getReturnType());
    }

    bool Function::hasBody(){
        return !function.isDeclaration();
    }

    Block* Function::getBody(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateBlock(&function.getEntryBlock());
    }

    std::list<Instruction*> Function::getInstructionsList(){
        std::list<Instruction*> instrctionsList = {};
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        for (auto &blk : function){
            for(auto &ins : blk) {
                instrctionsList.push_back(llvmToVanguard.translateInstruction(&ins));
            }
        }
        return instrctionsList;
    }

    llvm::Function* Function::unwrap(){
        return &function;
    }

}