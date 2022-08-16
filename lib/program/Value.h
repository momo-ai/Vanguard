#ifndef VANGUARD_PROGRAM_VALUE_H
#define VANGUARD_PROGRAM_VALUE_H

#include "Type.h"
#include <string>
#include "llvm/IR/Value.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Instruction.h"

namespace vanguard{
    class Value{
        public:
    };

    class Variable: public Value{
        public:
            virtual Type* getType() = 0;
            virtual bool hasName() = 0;
            virtual std::string getName() = 0;
    };

    class GlobalVariable: public Variable{
        public:
            explicit GlobalVariable(const llvm::GlobalVariable &);

            GlobalVariable(const GlobalVariable&) = delete;

            Type* getType() override;

            bool hasName() override;

            std::string getName() override;

            const llvm::GlobalVariable &unwrap();

        private:
            const llvm::GlobalVariable& globalVariable;
    };

    class Argument: public Variable{
        public:
            explicit Argument(const llvm::Argument&);

            Argument(const Argument&) = delete;

            Type* getType() override;

            bool hasName() override;

            std::string getName() override;

            const llvm::Argument &unwrap();

        private:
            const llvm::Argument& argument;
    };

    class InstructionVariable: public Variable{
        public:
            explicit InstructionVariable(const llvm::Instruction &);

            InstructionVariable(const InstructionVariable&) = delete;

            Type* getType() override;

            bool hasName() override;

            std::string getName() override;

            const llvm::Instruction &unwrap();

        private:
            const llvm::Instruction& instructionVariable;
    };

    template <class T>
    class Literal: Value{
        public:
            virtual T getValue() = 0;
    };

    class IntegerLiteral: Literal<int>{
        public:
            explicit IntegerLiteral(const llvm::ConstantInt &);

            IntegerLiteral(const IntegerLiteral&) = delete;

            int getValue() override;

            const llvm::ConstantInt &unwrap();

        private:
            const llvm::ConstantInt& constInt;
    };

    class StringLiteral: Literal<std::string>{
        public:
            explicit StringLiteral(const llvm::ConstantDataSequential &);

            StringLiteral(const StringLiteral&) = delete;

            std::string getValue() override;

            const llvm::ConstantDataSequential &unwrap();

        private:
            const llvm::ConstantDataSequential& constSeq;
    };

    class BooleanLiteral: public Literal<bool>{
        public:
            explicit BooleanLiteral(bool);

            BooleanLiteral(const BooleanLiteral&) = delete;

            bool getValue() override;
        
        private:
            bool constBool;
    };

    class MemoryAddress: public Value{
        public:
            MemoryAddress(const llvm::Value*,const llvm::Value*, unsigned long);

            MemoryAddress(const llvm::Value*, unsigned long);

            MemoryAddress(const MemoryAddress&) = delete;

            const llvm::Value* getPointer();

            const llvm::Value* getIndex();

            unsigned long getSize();

        private:
            const llvm::Value* pointer;
            const llvm::Value* index;
            unsigned long size = 0;
    };

}

#endif