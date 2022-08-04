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
            Value();
    };

    class Variable: Value{
        public:
            Variable();
            virtual Type* getType() = 0;
            virtual bool hasName() = 0;
            virtual std::string getName() = 0;
    };

    class GlobalVariable: Variable{
        public:
            GlobalVariable(llvm::GlobalVariable &);

            Type* getType() override;

            bool hasName() override;

            std::string getName() override;

        private:
            llvm::GlobalVariable& globalVariable;
    };

    class Argument: Variable{
        public:
            Argument(llvm::Argument&);

            Type* getType() override;

            bool hasName() override;

            std::string getName() override;
        private:
            llvm::Argument& argument;
    };

    class InstructionVariable: Variable{
        public:
            InstructionVariable(llvm::Instruction &);

            Type* getType() override;

            bool hasName() override;

            std::string getName() override;
        private:
            llvm::Instruction& instructionVariable;
    };

    template <class T>
    class Constant: Value{
        public:
            Constant();

            virtual T getValue()=0;
    };

    class ConstantInteger: Constant<int>{
        public:
            ConstantInteger(llvm::ConstantInt &);

            int getValue() override;

        private:
            llvm::ConstantInt& constInt;
    };

    class ConstantString: Constant<std::string>{
        public:
            ConstantString(llvm::ConstantDataSequential &);

            std::string getValue() override;

        private:
            llvm::ConstantDataSequential& constSeq;
    };

}

#endif