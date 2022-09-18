//
// Created by Jon Stephens on 8/26/22.
//

#ifndef VANGUARD_INSTRUCTIONCLASSES_H
#define VANGUARD_INSTRUCTIONCLASSES_H

#include "Base.h"


namespace vanguard {
    enum BinOp{Add, Sub, Mul, Div, Mod, Shl, Shr, And, Or, Xor, IFCmpInst};

    enum UnOp{Neg, Not};

    template<typename Domain> class InstructionClassVisitor;

    // Branch Instruction
    template<typename Domain>
    class BranchIns : public Domain::Instruction {
    public:
        template<typename ...Args>
        explicit BranchIns(Args&&... args) : Domain::Instruction(std::forward<Args>(args)...) {};

        static inline bool classof(const BranchIns &) { return true; }
        static inline bool classof(const BranchIns *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == BRANCH){ return true; }
            return false;
        }

        virtual bool isConditional() const = 0;
        virtual typename Domain::Value* condition() const = 0;
        virtual std::list<typename Domain::Block*> targets() const = 0;

        InstructionClassEnum instructionClass() const override {
            return BRANCH;
        }

        void accept(InstructionClassVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    //Return Instruction
    template<typename Domain>
    class ReturnIns : public Domain::Instruction {
    public:
        template<typename ...Args>
        explicit ReturnIns(Args&&... args) : Domain::Instruction(std::forward<Args>(args)...) {};

        static inline bool classof(const ReturnIns &) { return true; }
        static inline bool classof(const ReturnIns *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool cslassof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == RETURN){ return true; }
            return false;
        }

        virtual bool returnsValue() const = 0;
        virtual typename Domain::Value* value() const = 0;

        InstructionClassEnum instructionClass() const override {
            return RETURN;
        }

        void accept(InstructionClassVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class ErrorIns : public Domain::Instruction {
    public:
        template<typename ...Args>
        explicit ErrorIns(Args&&... args) : Domain::Instruction(std::forward<Args>(args)...) {};

        static inline bool classof(const ErrorIns &) { return true; }
        static inline bool classof(const ErrorIns *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == ERROR){ return true; }
            return false;
        }

        virtual std::string msg() const = 0;

        InstructionClassEnum instructionClass() const override {
            return ERROR;
        }

        void accept(InstructionClassVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class Expression : public Domain::Instruction {
    public:
        template<typename ...Args>
        explicit Expression(Args&&... args) : Domain::Instruction(std::forward<Args>(args)...) {};

        static inline bool classof(const Expression &) { return true; }
        static inline bool classof(const Expression *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() >= EXPRESSION_BEGIN && inst.instructionClass() <= EXPRESSION_END){ return true; }
            return false;
        }

        virtual typename Domain::Value* result() const = 0;
    };

    // Assign Instruction
    template<typename Domain>
    class AssignIns : public Expression<Domain> {
    public:
        template<typename ...Args>
        explicit AssignIns(Args&&... args) : Expression<Domain>(std::forward<Args>(args)...) {};

        static inline bool classof(const AssignIns &) { return true; }
        static inline bool classof(const AssignIns *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == ASSIGNMENT){ return true; }
            return false;
        }

        InstructionClassEnum instructionClass() const override {
            return ASSIGNMENT;
        }

        void accept(InstructionClassVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    //BinaryOpInstruction
    template<typename Domain>
    class BinaryOpIns : public Expression<Domain> {
    public:
        template<typename ...Args>
        explicit BinaryOpIns(Args&&... args) : Expression<Domain>(std::forward<Args>(args)...) {};
        static inline bool classof(const BinaryOpIns &) { return true; }
        static inline bool classof(const BinaryOpIns *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == BIN_OP){ return true; }
            return false;
        }

        virtual BinOp op() const  = 0;

        InstructionClassEnum instructionClass() const override {
            return BIN_OP;
        }

        void accept(InstructionClassVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    //Unary Operation Instruction
    template<typename Domain>
    class  UnaryOpIns : public Expression<Domain> {
    public:
        template<typename ...Args>
        explicit UnaryOpIns(Args&&... args) : Expression<Domain>(std::forward<Args>(args)...) {};

        static inline bool classof(const UnaryOpIns &) { return true; }
        static inline bool classof(const UnaryOpIns *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == UN_OP){ return true; }
            return false;
        }

        virtual UnOp op() const = 0;
        virtual typename Domain::Value* operand() const = 0;

        InstructionClassEnum instructionClass() const override {
            return UN_OP;
        }

        void accept(InstructionClassVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class CallIns : public Expression<Domain> {
    public:
        template<typename ...Args>
        explicit CallIns(Args&&... args) : Expression<Domain>(std::forward<Args>(args)...) {};

        static inline bool classof(const CallIns &) { return true; }
        static inline bool classof(const CallIns *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == CALL){ return true; }
            return false;
        }

        virtual bool hasReturn() const = 0;
        virtual std::vector<typename Domain::Function *> targets() const = 0;
        virtual std::list<typename Domain::Value*> args() const = 0;

        InstructionClassEnum instructionClass() const override {
            return CALL;
        }

        void accept(InstructionClassVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class CastIns : public Expression<Domain> {
    public:
        template<typename ...Args>
        explicit CastIns(Args&&... args) : Expression<Domain>(std::forward<Args>(args)...) {};

        static inline bool classof(const CastIns &) { return true; }
        static inline bool classof(const CastIns *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == CAST){ return true; }
            return false;
        }

        virtual typename Domain::Type *castTo() const = 0;

        InstructionClassEnum instructionClass() const override {
            return CAST;
        }

        void accept(InstructionClassVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class TernaryIns : public Expression<Domain> {
    public:
        template<typename ...Args>
        explicit TernaryIns(Args&&... args) : Expression<Domain>(std::forward<Args>(args)...) {};

        static inline bool classof(const TernaryIns &) { return true; }
        static inline bool classof(const TernaryIns *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == TERNARY){ return true; }
            return false;
        }

        virtual typename Domain::Value *condition() const = 0;
        virtual typename Domain::Value *trueValue() const = 0;
        virtual typename Domain::Value *falseValue() const = 0;

        InstructionClassEnum instructionClass() const override {
            return TERNARY;
        }

        void accept(InstructionClassVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class UnknownIns : public Expression<Domain> {
    public:
        template<typename ...Args>
        explicit UnknownIns(Args&&... args) : Expression<Domain>(std::forward<Args>(args)...) {};

        static inline bool classof(const UnknownIns &) { return true; }
        static inline bool classof(const UnknownIns *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == UNKNOWN){ return true; }
            return false;
        }

        InstructionClassEnum instructionClass() const override {
            return UNKNOWN;
        }

        void accept(InstructionClassVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class InstructionClassVisitor{
    public:
        virtual void visit(const BranchIns<Domain> &v) {};
        virtual void visit(const ReturnIns<Domain> &v) {};
        virtual void visit(const ErrorIns<Domain> &v) {};
        virtual void visit(const BinaryOpIns<Domain> &v) {};
        virtual void visit(const UnaryOpIns<Domain> &v) {};
        virtual void visit(const CallIns<Domain> &v) {};
        virtual void visit(const CastIns<Domain> &v) {};
        virtual void visit(const TernaryIns<Domain> &v) {};
        virtual void visit(const AssignIns<Domain> &v) {};
        virtual void visit(const UnknownIns<Domain> &v) {};
    };
}

#endif //VANGUARD_INSTRUCTIONCLASSES_H
