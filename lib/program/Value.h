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
//#include "LLVMtoVanguard.h"

namespace vanguard{

    enum ValueClassEnum{
        VARIABLE_BEGIN,
        GLOBAL_VARIABLE = VARIABLE_BEGIN,
        ARGUMENT,
        INSTRUCTION_VARIABLE,
        VARIABLE_END = INSTRUCTION_VARIABLE,
        LITERAL_BEGIN,
        INTEGER_LITERAL = LITERAL_BEGIN,
        STRING_LITERAL,
        BOOLEAN_LITERAL,
        LITERAL_END = BOOLEAN_LITERAL,
        MEMORY_ADDRESS_BEGIN,
        MEMORY_ADDRESS = MEMORY_ADDRESS_BEGIN,
        MEMORY_ADDRESS_END = MEMORY_ADDRESS,
        CONSTANT_BEGIN,
        CONSTANT = CONSTANT_BEGIN,
        CONSTANT_END = CONSTANT
    };

    class ValueClassVisitor;
    class Value{
    public:
        explicit Value(ValueClassEnum vc);

        static inline bool classof(const Value &) { return true; }
        static inline bool classof(const Value *) { return true; }

        virtual Type* getType() = 0;

        ValueClassEnum getClass() const;

        virtual void accept(ValueClassVisitor &v) const = 0;

    private:
        ValueClassEnum valueClass;
    };

    class Variable{
    public:
        virtual Type* getType() = 0;
        virtual bool hasName() = 0;
        virtual std::string getName() = 0;
    };

    class GlobalVariable: public Value, public Variable{
    public:
        explicit GlobalVariable(const llvm::GlobalVariable &);

        static inline bool classof(const GlobalVariable &) { return true; }
        static inline bool classof(const GlobalVariable *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.getClass() == GLOBAL_VARIABLE){ return true; }
            return false;
        }

        GlobalVariable(const GlobalVariable&) = delete;

        Type* getType() override;

        bool hasName() override;

        std::string getName() override;

        const llvm::GlobalVariable &unwrap();

        void accept(ValueClassVisitor &v) const override;

    private:
        const llvm::GlobalVariable& globalVariable;
    };

    class Argument: public Value, public Variable{
    public:
        explicit Argument(const llvm::Argument&);

        static inline bool classof(const Argument &) { return true; }
        static inline bool classof(const Argument *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.getClass() == ARGUMENT){ return true; }
            return false;
        }

        Argument(const Argument&) = delete;

        Type* getType() override;

        bool hasName() override;

        std::string getName() override;

        const llvm::Argument &unwrap();

        void accept(ValueClassVisitor &v) const override;

    private:
        const llvm::Argument& argument;
    };

    class InstructionVariable: public Value, public Variable{
    public:
        explicit InstructionVariable(const llvm::Instruction &);

        static inline bool classof(const InstructionVariable &) { return true; }
        static inline bool classof(const InstructionVariable *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.getClass() == INSTRUCTION_VARIABLE){ return true; }
            return false;
        }

        InstructionVariable(const InstructionVariable&) = delete;

        Type* getType() override;

        bool hasName() override;

        std::string getName() override;

        const llvm::Instruction &unwrap();

        void accept(ValueClassVisitor &v) const override;

    private:
        const llvm::Instruction& instructionVariable;
    };

    template <class T>
    class Literal{
    public:
        virtual T getValue() = 0;
    };

    class IntegerLiteral: public Value, public Literal<int>{
    public:
        explicit IntegerLiteral(const llvm::ConstantInt &);

        static inline bool classof(const IntegerLiteral &) { return true; }
        static inline bool classof(const IntegerLiteral *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.getClass() == INTEGER_LITERAL){ return true; }
            return false;
        }

        IntegerLiteral(const IntegerLiteral&) = delete;

        int getValue() override;

        Type* getType() override;

        const llvm::ConstantInt &unwrap();

        void accept(ValueClassVisitor &v) const override;

    private:
        const llvm::ConstantInt& constInt;
    };

    class StringLiteral: public Value, public Literal<std::string>{
    public:
        explicit StringLiteral(const llvm::ConstantDataSequential &);

        static inline bool classof(const StringLiteral &) { return true; }
        static inline bool classof(const StringLiteral *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.getClass() == STRING_LITERAL){ return true; }
            return false;
        }

        StringLiteral(const StringLiteral&) = delete;

        std::string getValue() override;

        Type* getType() override;

        const llvm::ConstantDataSequential &unwrap();

        void accept(ValueClassVisitor &v) const override;

    private:
        const llvm::ConstantDataSequential& constSeq;
    };

    class BooleanLiteral: public Literal<bool>{
    public:
        explicit BooleanLiteral(bool);

        static inline bool classof(const BooleanLiteral &) { return true; }
        static inline bool classof(const BooleanLiteral *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.getClass() == BOOLEAN_LITERAL){ return true; }
            return false;
        }

        BooleanLiteral(const BooleanLiteral&) = delete;

        bool getValue() override;

    private:
        bool constBool;
    };

    class MemoryAddress: public Value{
    public:
        MemoryAddress(const llvm::Value* ptr,const llvm::Value* idx, unsigned long sz);

        MemoryAddress(const llvm::Value* ptr, unsigned long sz);

        static inline bool classof(const MemoryAddress &) { return true; }
        static inline bool classof(const MemoryAddress *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.getClass() == MEMORY_ADDRESS){ return true; }
            return false;
        }

        MemoryAddress(const MemoryAddress&) = delete;

        const llvm::Value* getPointer();

        const llvm::Value* getIndex();

        unsigned long getSize();

        Type* getType() override;

        void accept(ValueClassVisitor &v) const override;

    private:
        const llvm::Value* pointer;
        const llvm::Value* index{};
        unsigned long size = 0;
    };

    class Constant: public Value{
    private:
        const llvm::Constant &constant;

    public:
        explicit Constant(const llvm::Constant &);

        static inline bool classof(const Constant &) { return true; }
        static inline bool classof(const Constant *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.getClass() == CONSTANT){ return true; }
            if (value.getClass() == STRING_LITERAL || value.getClass() == INTEGER_LITERAL){ return true; }
            return false;
        }

        Type* getType() override;

        void accept(ValueClassVisitor &v) const override;
    };

    class ValueClassVisitor{
    public:
        virtual void visit(const GlobalVariable &v) = 0;
        virtual void visit(const Argument &v) = 0;
        virtual void visit(const InstructionVariable &v) = 0;
        virtual void visit(const StringLiteral &v) = 0;
        virtual void visit(const IntegerLiteral &v) = 0;
        virtual void visit(const MemoryAddress &v) = 0;
        virtual void visit(const Constant &v) = 0;
    };
}

#endif