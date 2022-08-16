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

    std::list<Argument*> Function::getParams(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Argument*> params = {};
        for (auto itr = function.arg_begin(); itr != function.arg_end(); itr++){
            params.push_back((Argument *)llvmToVanguard.translateValue(llvm::dyn_cast<llvm::Value>(itr)));
        }
        return params;
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

    const llvm::Function &Function::unwrap(){
        return function;
    }

}