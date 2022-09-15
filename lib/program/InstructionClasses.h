//
// Created by Jon Stephens on 8/26/22.
//

#ifndef VANGUARD_INSTRUCTIONCLASSES_H
#define VANGUARD_INSTRUCTIONCLASSES_H

#include "Value.h"
#include "Universe.h"
#include "InstructionClassVisitor.h"


namespace vanguard {
    enum BinOp{Add, Sub, Mul, Div, Mod, Shl, Shr, And, Or, Xor, IFCmpInst};

    enum UnOp{Neg, Not};

    // Branch Instruction
    template<typename Base>
    class BranchIns : public Base::Instruction {
    public:
        template<typename ...Args>
        explicit BranchIns(Args&&... args) : Base::Instruction(std::forward<Args>(args)...) {};

        static inline bool classof(const BranchIns &) { return true; }
        static inline bool classof(const BranchIns *) { return true; }
        static inline bool classof(const Universe::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Universe::Instruction &inst) {
            if (inst.instructionClass() == BRANCH){ return true; }
            return false;
        }

        virtual bool isConditional() const = 0;
        virtual Value* condition() const = 0;
        virtual std::list<typename Base::Block*> targets() const = 0;

        InstructionClassEnum instructionClass() const override {
            return BRANCH;
        }

        void accept(InstructionClassVisitor<Base> &v) const override {
            v.visit(*this);
        }
    };

    //Return Instruction
    template<typename Base>
    class ReturnIns : public Base::Instruction {
    public:
        template<typename ...Args>
        explicit ReturnIns(Args&&... args) : Base::Instruction(std::forward<Args>(args)...) {};

        static inline bool classof(const ReturnIns &) { return true; }
        static inline bool classof(const ReturnIns *) { return true; }
        static inline bool classof(const Universe::Instruction *inst) { return classof(*inst); }
        static inline bool cslassof(const Universe::Instruction &inst) {
            if (inst.instructionClass() == RETURN){ return true; }
            return false;
        }

        virtual bool returnsValue() const = 0;
        virtual Value* value() const = 0;

        InstructionClassEnum instructionClass() const override {
            return RETURN;
        }

        void accept(InstructionClassVisitor<Base> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Base>
    class ErrorIns : public Base::Instruction {
    public:
        template<typename ...Args>
        explicit ErrorIns(Args&&... args) : Base::Instruction(std::forward<Args>(args)...) {};

        static inline bool classof(const ErrorIns &) { return true; }
        static inline bool classof(const ErrorIns *) { return true; }
        static inline bool classof(const typename Universe::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Universe::Instruction &inst) {
            if (inst.instructionClass() == ERROR){ return true; }
            return false;
        }

        virtual std::string msg() const = 0;

        InstructionClassEnum instructionClass() const override {
            return ERROR;
        }

        void accept(InstructionClassVisitor<Base> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Base>
    class Expression : public Base::Instruction {
    public:
        template<typename ...Args>
        explicit Expression(Args&&... args) : Base::Instruction(std::forward<Args>(args)...) {};

        static inline bool classof(const Expression &) { return true; }
        static inline bool classof(const Expression *) { return true; }
        static inline bool classof(const Universe::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Universe::Instruction &inst) {
            if (inst.instructionClass() >= EXPRESSION_BEGIN && inst.instructionClass() <= EXPRESSION_END){ return true; }
            return false;
        }

        virtual Value* result() const {
            auto* insVar = this->factory.createVal(this->ins);
            return insVar;
        }
    };

    // Assign Instruction
    template<typename Base>
    class AssignIns : public Expression<Base> {
    public:
        template<typename ...Args>
        explicit AssignIns(Args&&... args) : Expression<Base>(std::forward<Args>(args)...) {};

        static inline bool classof(const AssignIns &) { return true; }
        static inline bool classof(const AssignIns *) { return true; }
        static inline bool classof(const typename Universe::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Universe::Instruction &inst) {
            if (inst.instructionClass() == ASSIGNMENT){ return true; }
            return false;
        }

        InstructionClassEnum instructionClass() const override {
            return ASSIGNMENT;
        }

        void accept(InstructionClassVisitor<Base> &v) const override {
            v.visit(*this);
        }
    };

    //BinaryOpInstruction
    template<typename Base>
    class BinaryOpIns : public Expression<Base> {
    public:
        template<typename ...Args>
        explicit BinaryOpIns(Args&&... args) : Expression<Base>(std::forward<Args>(args)...) {};
        static inline bool classof(const BinaryOpIns &) { return true; }
        static inline bool classof(const BinaryOpIns *) { return true; }
        static inline bool classof(const typename Universe::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Universe::Instruction &inst) {
            if (inst.instructionClass() == BIN_OP){ return true; }
            return false;
        }

        virtual BinOp op() const  = 0;

        InstructionClassEnum instructionClass() const override {
            return BIN_OP;
        }

        void accept(InstructionClassVisitor<Base> &v) const override {
            v.visit(*this);
        }
    };

    //Unary Operation Instruction
    template<typename Base>
    class  UnaryOpIns : public Expression<Base> {
    public:
        template<typename ...Args>
        explicit UnaryOpIns(Args&&... args) : Expression<Base>(std::forward<Args>(args)...) {};

        static inline bool classof(const UnaryOpIns &) { return true; }
        static inline bool classof(const UnaryOpIns *) { return true; }
        static inline bool classof(const typename Universe::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Universe::Instruction &inst) {
            if (inst.instructionClass() == UN_OP){ return true; }
            return false;
        }

        virtual UnOp op() const = 0;
        virtual Value* operand() const = 0;

        InstructionClassEnum instructionClass() const override {
            return UN_OP;
        }

        void accept(InstructionClassVisitor<Base> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Base>
    class CallIns : public Expression<Base> {
    public:
        template<typename ...Args>
        explicit CallIns(Args&&... args) : Expression<Base>(std::forward<Args>(args)...) {};

        static inline bool classof(const CallIns &) { return true; }
        static inline bool classof(const CallIns *) { return true; }
        static inline bool classof(const typename Universe::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Universe::Instruction &inst) {
            if (inst.instructionClass() == CALL){ return true; }
            return false;
        }

        virtual bool hasReturn() const = 0;
        virtual std::vector<typename Base::Function *> targets() const = 0;
        virtual std::list<Value*> args() const = 0;

        InstructionClassEnum instructionClass() const override {
            return CALL;
        }

        void accept(InstructionClassVisitor<Base> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Base>
    class CastIns : public Expression<Base> {
    public:
        template<typename ...Args>
        explicit CastIns(Args&&... args) : Expression<Base>(std::forward<Args>(args)...) {};

        static inline bool classof(const CastIns &) { return true; }
        static inline bool classof(const CastIns *) { return true; }
        static inline bool classof(const typename Universe::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Universe::Instruction &inst) {
            if (inst.instructionClass() == CAST){ return true; }
            return false;
        }

        virtual Type *castTo() const = 0;

        InstructionClassEnum instructionClass() const override {
            return CAST;
        }

        void accept(InstructionClassVisitor<Base> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Base>
    class TernaryIns : public Expression<Base> {
    public:
        template<typename ...Args>
        explicit TernaryIns(Args&&... args) : Expression<Base>(std::forward<Args>(args)...) {};

        static inline bool classof(const TernaryIns &) { return true; }
        static inline bool classof(const TernaryIns *) { return true; }
        static inline bool classof(const typename Universe::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Universe::Instruction &inst) {
            if (inst.instructionClass() == TERNARY){ return true; }
            return false;
        }

        virtual Value *condition() const = 0;
        virtual Value *trueValue() const = 0;
        virtual Value *falseValue() const = 0;

        InstructionClassEnum instructionClass() const override {
            return TERNARY;
        }

        void accept(InstructionClassVisitor<Base> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Base>
    class UnknownIns : public Expression<Base> {
    public:
        template<typename ...Args>
        explicit UnknownIns(Args&&... args) : Expression<Base>(std::forward<Args>(args)...) {};

        static inline bool classof(const UnknownIns &) { return true; }
        static inline bool classof(const UnknownIns *) { return true; }
        static inline bool classof(const typename Universe::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Universe::Instruction &inst) {
            if (inst.instructionClass() == UNKNOWN){ return true; }
            return false;
        }

        InstructionClassEnum instructionClass() const override {
            return UNKNOWN;
        }

        void accept(InstructionClassVisitor<Base> &v) const override {
            v.visit(*this);
        }
    };
}

#endif //VANGUARD_INSTRUCTIONCLASSES_H
