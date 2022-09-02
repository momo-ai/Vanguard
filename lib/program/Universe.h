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
            explicit CompilationUnit(UnitFactory &factory, const llvm::Module& mod);
            CompilationUnit(const CompilationUnit&) = delete;
            std::string name();
            std::string sourceFile();
            Universe::Function* findFunction(std::string name);
            Value* findGlobalVariable(std::string name);
            virtual std::list<Universe::Function *> functions();
            virtual std::list<Value*> globalVariables();
            const llvm::Module& unwrap();
        protected:
            UnitFactory &factory;
        private:
            const llvm::Module& module;
        };

        class Function {
        public:
            explicit Function(UnitFactory &factory, const llvm::Function &func);
            Function(const Function&) = delete;
            std::string name();
            virtual std::list<Variable*> params();
            virtual Type* returnType();
            bool hasBody();
            Block* body();
            virtual std::list<Instruction*> instructions();
            virtual std::list<Block *> blocks();
            const llvm::Function &unwrap();
        protected:
            const llvm::Function &function;
            UnitFactory &factory;
        };

        class Block {
        public:
            explicit Block(UnitFactory &factory, const llvm::BasicBlock &block);
            Block(const Block&) = delete;
            std::string name();
            Function* parent();
            std::list<Instruction *> instructions();
            bool isEntry();
            std::unordered_set<Block *> successors();
            const llvm::BasicBlock& unwrap();
        protected:
            const llvm::BasicBlock& block;
            UnitFactory &factory;
        };

        class Instruction {
        public:
            static inline bool classof(const Instruction &) { return true; }
            static inline bool classof(const Instruction *) { return true; }

            virtual InstructionClassEnum instructionClass() const = 0;
            virtual std::string name() const = 0;
            virtual Block* parent() const = 0;
            virtual bool mayReadOrWriteToMemory() const = 0;
            virtual bool willReturn() const = 0;
            virtual Instruction * getSuccessor() const = 0;
            virtual std::list<Universe::Instruction*> getAllSuccessors() const = 0;
            virtual Value* operand(unsigned i) const = 0;
            virtual unsigned numOperands() const = 0;
            virtual const llvm::Instruction &unwrap() const = 0;
            virtual void accept(InstructionClassVisitor &v) const = 0;
        };

        explicit Universe(UnitFactory &factory, const std::vector<std::unique_ptr<llvm::Module>>& modules);
        const std::vector<CompilationUnit *> &units();

    private:
        std::vector<CompilationUnit *> programUnits;
    };
}



#endif //VANGUARD_UNIVERSE_H
