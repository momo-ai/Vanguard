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

    class Variable: Value{
        public:
            virtual Type* getType() = 0;
            virtual bool hasName() = 0;
            virtual std::string getName() = 0;
    };

    class GlobalVariable: Variable{
        public:
            explicit GlobalVariable(const llvm::GlobalVariable &);

            GlobalVariable(const GlobalVariable&) = delete;

            Type* getType() override;

            bool hasName() override;

            std::string getName() override;

        private:
            const llvm::GlobalVariable& globalVariable;
    };

    class Argument: Variable{
        public:
            explicit Argument(const llvm::Argument&);

            Argument(const Argument&) = delete;

            Type* getType() override;

            bool hasName() override;

            std::string getName() override;
        private:
            const llvm::Argument& argument;
    };

    class InstructionVariable: Variable{
        public:
            explicit InstructionVariable(const llvm::Instruction &);

            InstructionVariable(const InstructionVariable&) = delete;

            Type* getType() override;

            bool hasName() override;

            std::string getName() override;
        private:
            const llvm::Instruction& instructionVariable;
    };

    template <class T>
    class Literal: Value{
        public:
            virtual T getValue()=0;
    };

    class IntegerLiteral: Literal<int>{
        public:
            explicit IntegerLiteral(const llvm::ConstantInt &);

            IntegerLiteral(const IntegerLiteral&) = delete;

            int getValue() override;

        private:
            const llvm::ConstantInt& constInt;
    };

    class StringLiteral: Literal<std::string>{
        public:
            explicit StringLiteral(const llvm::ConstantDataSequential &);

            StringLiteral(const StringLiteral&) = delete;

            std::string getValue() override;

        private:
            const llvm::ConstantDataSequential& constSeq;
    };

}

#endif