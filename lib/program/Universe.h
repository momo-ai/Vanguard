//
// Created by Jon Stephens on 8/20/22.
//

#ifndef VANGUARD_UNIVERSE_H
#define VANGUARD_UNIVERSE_H

#include <vector>
#include <llvm/IR/Module.h>
#include <list>
#include <unordered_set>
#include "Type.h"

namespace vanguard {
    class UnitFactory;
    class Variable;
    class Value;

    enum InstructionClassEnum {
        BRANCH,
        RETURN,
        ERROR,
        EXPRESSION_BEGIN,
        BIN_OP = EXPRESSION_BEGIN,
        UN_OP,
        CALL,
        CAST,
        TERNARY,
        ASSIGNMENT,
        UNKNOWN,
        EXPRESSION_END = UNKNOWN
    };

    class InstructionClassVisitor;

    class Universe {
    public:
        class CompilationUnit;
        class Function;
        class Block;
        class Instruction;

        class CompilationUnit {
        public:
            explicit CompilationUnit(UnitFactory &factory, const llvm::Module* mod);
            CompilationUnit(const CompilationUnit&) = delete;
            std::string name();
            std::string sourceFile();
            Universe::Function* findFunction(std::string name);
            Value* findGlobalVariable(std::string name);
            virtual std::list<Universe::Function *> functions();
            virtual std::list<Value*> globalVariables();
            const llvm::Module* unwrap();
        protected:
            UnitFactory &factory;
        private:
            const llvm::Module* module;
        };

        class Function {
        public:
            explicit Function(UnitFactory &factory, const llvm::Function *func);
            Function(const Function&) = delete;
            virtual std::string name() const;
            virtual std::vector<Variable*> params() const;
            virtual Type* returnType() const;
            virtual bool hasBody() const;
            virtual Block* body() const;
            virtual std::vector<Instruction*> instructions() const;
            virtual std::vector<Block *> blocks() const;
            const llvm::Function *unwrap();
        protected:
            const llvm::Function *function;
            UnitFactory &factory;
        };

        class Block {
        public:
            explicit Block(UnitFactory &factory, const llvm::BasicBlock *block);
            Block(const Block&) = delete;
            std::string name();
            Function* parent();
            std::list<Instruction *> instructions();
            bool isEntry();
            std::unordered_set<Block *> successors();
            const llvm::BasicBlock* unwrap();
        protected:
            const llvm::BasicBlock* block;
            UnitFactory &factory;
        };

        class Instruction {
        public:
            explicit Instruction(UnitFactory &factory) : factory(factory) {};
            static inline bool classof(const Instruction &) { return true; }
            static inline bool classof(const Instruction *) { return true; }

            virtual InstructionClassEnum instructionClass() const = 0;
            virtual std::string name() const = 0;
            virtual Block* parent() const = 0;
            virtual bool willReturn() const = 0;
            virtual Value* operand(unsigned i) const = 0;
            virtual unsigned numOperands() const = 0;
            virtual const llvm::Instruction &unwrap() const = 0;
            virtual void accept(InstructionClassVisitor &v) const = 0;
        protected:
            UnitFactory &factory;
        };

        explicit Universe(UnitFactory &factory, std::vector<CompilationUnit *>  units);
        const std::vector<CompilationUnit *> &units() const;

    private:
        std::vector<CompilationUnit *> programUnits;
    };
}



#endif //VANGUARD_UNIVERSE_H
