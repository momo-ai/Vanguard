#include "Function.h"
#include "Block.h"
#include "LLVMtoVanguard.h"
#include "llvm/IR/InstIterator.h"

namespace vanguard{
    
    Function::Function(const llvm::Function& func): function(func){
    }

    std::string Function::name(){
        return function.getName().str();
    }

    std::list<Argument*> Function::params(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Argument*> params = {};
        for (auto itr = function.arg_begin(); itr != function.arg_end(); itr++){
            params.push_back((Argument *)llvmToVanguard.translateValue(llvm::dyn_cast<llvm::Value>(itr)));
        }
        return params;
    }

    Type* Function::returnType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(function.getReturnType());
    }

    bool Function::hasBody(){
        return !function.isDeclaration();
    }

    Block* Function::body(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateBlock(&function.getEntryBlock());
    }

    std::list<Instruction*> Function::instructions(){
        std::list<Instruction*> instructionsList = {};
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        for (auto &blk : function){
            for(auto &ins : blk) {
                instructionsList.push_back(llvmToVanguard.translateInstruction(&ins));
            }
        }
        return instructionsList;
    }

    std::list<Block *> Function::blocks(){
        std::list<Block *> blocks = {};
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        for (auto &blk : function){
            blocks.push_back(llvmToVanguard.translateBlock(&blk));
        }
        return blocks;
    }

    const llvm::Function &Function::unwrap(){
        return function;
    }

}