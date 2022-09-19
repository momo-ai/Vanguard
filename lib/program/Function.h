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
        explicit Function(const llvm::Function* func): function(func){}
        Function(const Function&) = delete;
        virtual std::string name() const {
            return function->getName().str();
        }

        virtual std::vector<vanguard::Variable<Domain>*> params() const {
            std::vector<vanguard::Variable<Domain>*> params = {};
            auto &factory = Domain::Factory::instance();
            for (auto itr = function->arg_begin(); itr != function->arg_end(); itr++){
                params.push_back((vanguard::Variable<Domain> *) factory.createVal(itr));
            }
            return params;
        }

        virtual typename Domain::Type* returnType() const {
            auto &factory = Domain::Factory::instance();
            return factory.createType(function->getReturnType());
        }

        virtual bool hasBody() const  {
            return !function->isDeclaration();
        }

        const llvm::Function *unwrap() {
            return function;
        }

        virtual typename Domain::CompilationUnit *unit() const {
            auto &factory = Domain::Factory::instance();
            return factory.createUnit(function->getParent());
        }

        virtual typename Domain::Block* body() const {
            auto &factory = Domain::Factory::instance();
            return factory.createBlk(&function->getEntryBlock());
        }

        virtual std::vector<typename Domain::Instruction*> instructions() const {
            std::vector<typename Domain::Instruction*> instructionsList = {};
            auto &factory = Domain::Factory::instance();
            for (auto &blk : *function){
                for(auto &ins : blk) {
                    instructionsList.push_back(factory.createIns(&ins));
                }
            }
            return instructionsList;
        }

        virtual std::vector<typename Domain::Block *> blocks() const {
            std::vector<Block *> blocks = {};
            auto &factory = Domain::Factory::instance();
            for (auto &blk : *function){
                blocks.push_back(factory.createBlk(&blk));
            }
            return blocks;
        }
    protected:
        const llvm::Function *function;
    };
}

#endif