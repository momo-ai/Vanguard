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
            Value* findGlobalVariable(std::string name);
            virtual std::list<Value*> globalVariables();
            const llvm::Module* unwrap();
        protected:
            Universe::Function* findFn(std::string name);
            virtual std::list<Universe::Function *> fns();
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
            const llvm::Function *unwrap();
        protected:
            virtual Block* head() const;
            virtual std::vector<Instruction*> insts() const;
            virtual std::vector<Block *> blks() const;
            const llvm::Function *function;
            UnitFactory &factory;
        };

        class Block {
        public:
            explicit Block(UnitFactory &factory, const llvm::BasicBlock *block);
            Block(const Block&) = delete;
            virtual std::string name();
            virtual bool isEntry();
            virtual const llvm::BasicBlock* unwrap();
        protected:
            virtual Function* fn();
            virtual std::list<Instruction *> insts();
            virtual std::unordered_set<Block *> succs();

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
