#ifndef VANGUARD_FUNCTION_H
#define VANGUARD_FUNCTION_H

#include "Base.h"
#include "llvm/IR/InstIterator.h"
#include <iostream>
#include "ValueClasses.h"

namespace vanguard{
    template<typename Domain>
    class Base<Domain>::Function {
    public:
        explicit Function(typename Domain::Factory &factory, const llvm::Function* func): factory(factory), function(func){}
        Function(const Function&) = delete;
        virtual std::string name() const {
            return function->getName().str();
        }

        virtual std::vector<vanguard::Variable<Domain>*> params() const {
            std::vector<vanguard::Variable<Domain>*> params = {};
            for (auto itr = function->arg_begin(); itr != function->arg_end(); itr++){
                params.push_back((vanguard::Variable<Domain> *) factory.createVal(itr));
            }
            return params;
        }

        virtual typename Domain::Type* returnType() const {
            return factory.createType(function->getReturnType());
        }

        virtual bool hasBody() const  {
            return !function->isDeclaration();
        }

        const llvm::Function *unwrap() {
            return function;
        }

        virtual typename Domain::CompilationUnit *unit() const {
            return factory.createUnit(function->getParent());
        }

        virtual typename Domain::Block* body() const {
            return factory.createBlk(&function->getEntryBlock());
        }

        virtual std::vector<typename Domain::Instruction*> instructions() const {
            std::vector<Instruction*> instructionsList = {};
            for (auto &blk : *function){
                for(auto &ins : blk) {
                    instructionsList.push_back(factory.createIns(&ins));
                }
            }
            return instructionsList;
        }

        virtual std::vector<typename Domain::Block *> blocks() const {
            std::vector<Block *> blocks = {};
            for (auto &blk : *function){
                blocks.push_back(factory.createBlk(&blk));
            }
            return blocks;
        }
    protected:
        const llvm::Function *function;
        typename Domain::Factory &factory;
    };


    /*template<typename Domain>
    Universe<Domain>::Function::Function(Factory &factory, const llvm::Function* func): factory(factory), function(func){}

    template<typename Domain>
    std::string Universe<Domain>::Function::name() const {
        return function->getName().str();
    }

    template<typename Domain>
    std::vector<vanguard::Variable<Domain>*> Universe<Domain>::Function::params() const {
        std::vector<vanguard::Variable<Domain>*> params = {};
        for (auto itr = function->arg_begin(); itr != function->arg_end(); itr++){
            params.push_back((vanguard::Variable<Domain> *) factory.createVal(itr));
        }
        return params;
    }

    template<typename Domain>
    typename Domain::Type* Universe<Domain>::Function::returnType() const {
        return factory.createType(function->getReturnType());
    }

    template<typename Domain>
    bool Universe<Domain>::Function::hasBody() const {
        return !function->isDeclaration();
    }

    template<typename Domain>
    typename Domain::Block* Universe<Domain>::Function::body() const {
        return factory.createBlk(&function->getEntryBlock());
    }

    template<typename Domain>
    std::vector<typename Domain::Instruction*> Universe<Domain>::Function::instructions() const {
        std::vector<Instruction*> instructionsList = {};
        for (auto &blk : *function){
            for(auto &ins : blk) {
                instructionsList.push_back(factory.createIns(&ins));
            }
        }
        return instructionsList;
    }

    template<typename Domain>
    std::vector<typename Domain::Block *> Universe<Domain>::Function::blocks() const {
        std::vector<Block *> blocks = {};
        for (auto &blk : *function){
            blocks.push_back(factory.createBlk(&blk));
        }
        return blocks;
    }

    template<typename Domain>
    const llvm::Function *Universe<Domain>::Function::unwrap(){
        return function;
    }

    template<typename Domain>
    typename Domain::CompilationUnit *Universe<Domain>::Function::unit() const {
        return factory.createUnit(function->getParent());
    }*/
}

#endif