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

    class Variable: public Value{
        public:
            Variable();
            virtual Type* getType() = 0;
            virtual bool hasName() = 0;
            virtual std::string getName() = 0;
    };

    class GlobalVariable: public Variable{
        public:
            GlobalVariable(llvm::GlobalVariable &);

            Type* getType() override;

            bool hasName() override;

            std::string getName() override;

            llvm::GlobalVariable* unwrap();

        private:
            llvm::GlobalVariable& globalVariable;
    };

    class Argument: public Variable{
        public:
            Argument(llvm::Argument&);

            Type* getType() override;

            bool hasName() override;

            std::string getName() override;

            llvm::Argument* unwrap();

        private:
            llvm::Argument& argument;
    };

    class InstructionVariable: public Variable{
        public:
            InstructionVariable(llvm::Instruction &);

            Type* getType() override;

            bool hasName() override;

            std::string getName() override;

            llvm::Instruction* unwrap();

        private:
            llvm::Instruction& instructionVariable;
    };

    template <class T>
    class Constant: public Value{
        public:
            Constant();

            virtual T getValue()=0;
    };

    class ConstantInteger: public Constant<int>{
        public:
            ConstantInteger(llvm::ConstantInt &);

            int getValue() override;

            llvm::ConstantInt* unwrap();

        private:
            llvm::ConstantInt& constInt;
    };

    class ConstantString: public Constant<std::string>{
        public:
            ConstantString(llvm::ConstantDataSequential &);

            std::string getValue() override;

            llvm::ConstantDataSequential* unwrap();

        private:
            llvm::ConstantDataSequential& constSeq;
    };

    class ConstantBoolean: public Constant<bool>{
        public:
            ConstantBoolean(bool);

            bool getValue() override;
        
        private:
            bool constBool;
    };

    class MemoryAddress: public Value{
        public:
            MemoryAddress(llvm::Value*, llvm::Value*, unsigned);

            llvm::Value* getPointer();

            llvm::Value* getIndex();

            unsigned getSize();

        private:
            llvm::Value* pointer;
            llvm::Value* index;
            unsigned size;
    };

}

#endif