#ifndef VANGUARD_PROGRAM_VALUE_H
#define VANGUARD_PROGRAM_VALUE_H

#include "Universe.h"
#include <string>
#include "llvm/IR/Value.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Instruction.h"

namespace vanguard{
    enum ValueClassEnum{
        VARIABLE,
        CONSTANT,
        LITERAL,
        POINTER,
        MEMORY_REGION,
        LOCATION,
    };

    class UnitFactory;
    class ValueClassVisitor;

    class Value{
    public:
        explicit Value(UnitFactory &factory, ValueClassEnum vc);

        static inline bool classof(const Value &) { return true; }
        static inline bool classof(const Value *) { return true; }

        virtual Type* type() const = 0;

        ValueClassEnum valueClass() const;

        virtual void accept(ValueClassVisitor &v) const = 0;

    protected:
        ValueClassEnum valClass;
        UnitFactory &factory;
    };

    class Variable : public Value {
    public:
        explicit Variable(UnitFactory &factory) : Value(factory, VARIABLE) {};

        static inline bool classof(const Variable &) { return true; }
        static inline bool classof(const Variable *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == VARIABLE){ return true; }
            return false;
        }

        virtual bool hasName() const = 0;
        virtual std::string name() const = 0;
        void accept(ValueClassVisitor &v) const override;
    };

    class Constant : public Value {
    public:
        explicit Constant(UnitFactory &factory) : Value(factory, CONSTANT) {};
        static inline bool classof(const Constant &) { return true; }
        static inline bool classof(const Constant *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == CONSTANT){ return true; }
            return false;
        }
        void accept(ValueClassVisitor &v) const override;
    };

    //template<typename LitType>
    class Literal : public Value {
    public:
        explicit Literal(UnitFactory &factory) : Value(factory, LITERAL) {};
        static inline bool classof(const Literal &) { return true; }
        static inline bool classof(const Literal *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == LITERAL){ return true; }
            return false;
        }

        //virtual LitType value() const = 0;
        void accept(ValueClassVisitor &v) const override;
    };

    class Pointer : public Value {
    public:
        explicit Pointer(UnitFactory &factory) : Value(factory, POINTER) {};
        static inline bool classof(const Pointer &) { return true; }
        static inline bool classof(const Pointer *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == POINTER){ return true; }
            return false;
        }

        virtual Value *base() const = 0;
        virtual Value *offset() const = 0;
        //virtual Type *refType() const = 0;
        void accept(ValueClassVisitor &v) const override;
    };

    class MemoryRegion : public Value {
    public:
        explicit MemoryRegion(UnitFactory &factory) : Value(factory, MEMORY_REGION) {};
        static inline bool classof(const MemoryRegion &) { return true; }
        static inline bool classof(const MemoryRegion *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == MEMORY_REGION){ return true; }
            return false;
        }

        /*virtual const Pointer *pointer() const = 0;
        virtual unsigned long size() const = 0;*/
        void accept(ValueClassVisitor &v) const override;
    };

    class Location : public Value {
    public:
        explicit Location(UnitFactory &factory) : Value(factory, LOCATION) {};
        static inline bool classof(const Location &) { return true; }
        static inline bool classof(const Location *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == LOCATION){ return true; }
            return false;
        }

        virtual Universe::Block &loc() const = 0;
        void accept(ValueClassVisitor &v) const override;
    };

    class ValueClassVisitor{
    public:
        virtual void visit(const Variable &v) = 0;
        virtual void visit(const Constant &v) = 0;
        virtual void visit(const Literal &v) = 0;
        virtual void visit(const Pointer &v) = 0;
        virtual void visit(const MemoryRegion &v) = 0;
        virtual void visit(const Location &v) = 0;
    };











    /*class GlobalVariable: public Variable{
    public:
        explicit GlobalVariable(UnitFactory &factory, const llvm::GlobalVariable &);

        static inline bool classof(const GlobalVariable &) { return true; }
        static inline bool classof(const GlobalVariable *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == GLOBAL_VARIABLE){ return true; }
            return false;
        }

        GlobalVariable(const GlobalVariable&) = delete;

        Type* type() const override;

        bool hasName() const override;

        std::string name() const override;

        const llvm::GlobalVariable &unwrap() const;

        void accept(ValueClassVisitor &v) const override;

    private:
        const llvm::GlobalVariable& globalVariable;
    };

    class Argument: public Variable{
    public:
        explicit Argument(UnitFactory &factory, const llvm::Argument&);

        static inline bool classof(const Argument &) { return true; }
        static inline bool classof(const Argument *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == ARGUMENT){ return true; }
            return false;
        }

        Argument(const Argument&) = delete;

        Type* type() const override;

        bool hasName() const override;

        std::string name() const override;

        const llvm::Argument &unwrap() const;

        void accept(ValueClassVisitor &v) const override;

    private:
        const llvm::Argument& argument;
    };

    class InstructionVariable: public Variable{
    public:
        explicit InstructionVariable(UnitFactory &factory, const llvm::Instruction &);

        static inline bool classof(const InstructionVariable &) { return true; }
        static inline bool classof(const InstructionVariable *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == INSTRUCTION_VARIABLE){ return true; }
            return false;
        }

        InstructionVariable(const InstructionVariable&) = delete;

        Type* type() const override;

        bool hasName() const override;

        std::string name() const override;

        const llvm::Instruction &unwrap() const;

        void accept(ValueClassVisitor &v) const override;

    private:
        const llvm::Instruction& instructionVariable;
    };

    template <class T>
    class Literal : public Value {
    public:
        Literal(UnitFactory &factory, ValueClassEnum vc) : Value(factory, vc) {};
        virtual T value() const = 0;
    };

    class IntegerLiteral: public Literal<int>{
    public:
        explicit IntegerLiteral(UnitFactory &factory, const llvm::ConstantInt &);

        static inline bool classof(const IntegerLiteral &) { return true; }
        static inline bool classof(const IntegerLiteral *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == INTEGER_LITERAL){ return true; }
            return false;
        }

        IntegerLiteral(const IntegerLiteral&) = delete;

        int value() const override;

        Type* type() const override;

        const llvm::ConstantInt &unwrap() const;

        void accept(ValueClassVisitor &v) const override;

    private:
        const llvm::ConstantInt& constInt;
    };

    class StringLiteral: public Literal<std::string>{
    public:
        explicit StringLiteral(UnitFactory &factory, const llvm::ConstantDataSequential &);

        static inline bool classof(const StringLiteral &) { return true; }
        static inline bool classof(const StringLiteral *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == STRING_LITERAL){ return true; }
            return false;
        }

        StringLiteral(const StringLiteral&) = delete;

        std::string value() const override;

        Type* type() const override;

        const llvm::ConstantDataSequential &unwrap() const;

        void accept(ValueClassVisitor &v) const override;

    private:
        const llvm::ConstantDataSequential& constSeq;
    };

    class BooleanLiteral: public Literal<bool>{
    public:
        explicit BooleanLiteral(UnitFactory &factory, bool b);

        static inline bool classof(const BooleanLiteral &) { return true; }
        static inline bool classof(const BooleanLiteral *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == BOOLEAN_LITERAL){ return true; }
            return false;
        }

        BooleanLiteral(const BooleanLiteral&) = delete;

        bool value() const override;

    private:
        bool constBool;
    };

    class Pointer : public Value {
    public:
        Pointer(UnitFactory &factory, const llvm::Value *base, const llvm::Value *offset, const llvm::Type *type);

        static inline bool classof(const Pointer &) { return true; }
        static inline bool classof(const Pointer *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == POINTER){ return true; }
            return false;
        }

        Pointer(const Pointer&) = delete;
        Value *base() const;
        Value *offset() const;
        Type *refType() const;
        Type* type() const override;
        void accept(ValueClassVisitor &v) const override;
    private:
        const llvm::Value *ptrBase;
        const llvm::Value *ptrOffset;
        const llvm::Type *ptrType;
    };

    class MemoryRegion: public Value{
    public:
        MemoryRegion(UnitFactory &factory, const Pointer *ptr, unsigned long size);

        static inline bool classof(const MemoryRegion &) { return true; }
        static inline bool classof(const MemoryRegion *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == MEMORY_REGION){ return true; }
            return false;
        }

        MemoryRegion(const MemoryRegion&) = delete;

        const Pointer *pointer() const;

        unsigned long size() const;

        Type* type() const override;

        //Type* type() const override;

        //const llvm::Value* getLLVMPointer() const;

        //const llvm::Value* getLLVMIndex() const;

        void accept(ValueClassVisitor &v) const override;

    private:
        const Pointer *ptr;
        unsigned long memSize = 0;
    };

    class Constant: public Value{
    private:
        const llvm::Constant &constant;

    public:
        explicit Constant(UnitFactory &factory, const llvm::Constant &);

        static inline bool classof(const Constant &) { return true; }
        static inline bool classof(const Constant *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == CONSTANT){ return true; }
            return false;
        }

        Type* type() const override;

        unsigned getLLVMValueID() const;

        void accept(ValueClassVisitor &v) const override;
    };

    class Location: public Value{
    private:
        const llvm::BasicBlock &location;

    public:
        explicit Location(UnitFactory &factory, const llvm::BasicBlock &);

        static inline bool classof(const Location &) { return true; }
        static inline bool classof(const Location *) { return true; }
        static inline bool classof(const Value *value) { return classof(*value); }
        static inline bool classof(const Value &value) {
            if (value.valueClass() == LOCATION){ return true; }
            return false;
        }

        Type* type() const override;
        void accept(ValueClassVisitor &v) const override;
        Universe::Block &loc() const;
    };

    class ValueClassVisitor{
    public:
        virtual void visit(const Variable &v) = 0;
        virtual void visit(const GlobalVariable &v) = 0;
        virtual void visit(const Argument &v) = 0;
        virtual void visit(const InstructionVariable &v) = 0;
        virtual void visit(const StringLiteral &v) = 0;
        virtual void visit(const IntegerLiteral &v) = 0;
        virtual void visit(const Pointer &v) = 0;
        virtual void visit(const MemoryRegion &v) = 0;
        virtual void visit(const Constant &v) = 0;
        virtual void visit(const Location &v) = 0;
    };*/
}

#endif