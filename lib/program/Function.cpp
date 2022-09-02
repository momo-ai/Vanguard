#include "Universe.h"
#include "LLVMFactory.h"
#include "llvm/IR/InstIterator.h"

namespace vanguard{
    
    Universe::Function::Function(UnitFactory &factory, const llvm::Function& func): factory(factory), function(func){
    }

    std::string Universe::Function::name(){
        return function.getName().str();
    }

    std::list<Variable*> Universe::Function::params(){
        std::list<Variable*> params = {};
        for (auto itr = function.arg_begin(); itr != function.arg_end(); itr++){
            params.push_back((Variable *) factory.createVal(itr));
        }
        return params;
    }

    Type* Universe::Function::returnType(){
        return factory.createType(function.getReturnType());
    }

    bool Universe::Function::hasBody(){
        return !function.isDeclaration();
    }

    Universe::Block* Universe::Function::body(){
        return factory.createBlk(&function.getEntryBlock());
    }

    std::list<Universe::Instruction*> Universe::Function::instructions(){
        std::list<Instruction*> instructionsList = {};
        for (auto &blk : function){
            for(auto &ins : blk) {
                instructionsList.push_back(factory.createIns(&ins));
            }
        }
        return instructionsList;
    }

    std::list<Universe::Block *> Universe::Function::blocks(){
        std::list<Block *> blocks = {};
        for (auto &blk : function){
            blocks.push_back(factory.createBlk(&blk));
        }
        return blocks;
    }

    const llvm::Function &Universe::Function::unwrap(){
        return function;
    }

}