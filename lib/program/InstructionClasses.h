//
// Created by Jon Stephens on 8/26/22.
//

#ifndef VANGUARD_INSTRUCTIONCLASSES_H
#define VANGUARD_INSTRUCTIONCLASSES_H

#include "Value.h"
#include "Universe.h"

namespace vanguard {
    enum BinOp{Add, Sub, Mul, Div, Mod, Shl, Shr, And, Or, Xor, IFCmpInst};

    enum UnOp{Neg, Not};

    /*template<typename Wrapped>
    class Universe::Instruction::Common {

    };

    template<typename Wrapped>
    class Universe::Instruction::Branch {

    };

    template<typename Wrapped>
    class Universe::Instruction::Return {

    };

    template<typename Wrapped>
    class Universe::Instruction::Error {

    };

    template<typename Wrapped>
    class Universe::Instruction::Assignment {

    };

    template<typename Wrapped>
    class Universe::Instruction::BinaryOpExpr {

    };

    template<typename Wrapped>
    class Universe::Instruction::UnaryOpExpr {

    };

    template<typename Wrapped>
    class Universe::Instruction::CallExpr {

    };

    template<typename Wrapped>
    class Universe::Instruction::CastExpr {

    };

    template<typename Wrapped>
    class Universe::Instruction::TernaryExpr {

    };

    template<typename Wrapped>
    class Universe::Instruction::UnknownExpr {

    };*/

    // Branch Instruction
    template<typename Domain>
    class Branch : public Domain::Instruction {
    public:
        explicit Branch(UnitFactory &factory) : Domain::Instruction(factory) {};

        static inline bool classof(const Branch &) { return true; }
        static inline bool classof(const Branch *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == BRANCH){ return true; }
            return false;
        }

        virtual bool isConditional() const = 0;
        virtual Value* condition() const = 0;
        virtual std::list<Universe::Block*> targets() const = 0;

        InstructionClassEnum instructionClass() const override {
            return BRANCH;
        }
    };

    //Return Instruction
    template<typename Domain>
    class Return : public Domain::Instruction {
    public:
        explicit Return(UnitFactory &factory) : Domain::Instruction(factory) {};
        static inline bool classof(const Return &) { return true; }
        static inline bool classof(const Return *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == RETURN){ return true; }
            return false;
        }

        virtual bool returnsValue() const = 0;
        virtual Value* value() const = 0;

        InstructionClassEnum instructionClass() const override {
            return RETURN;
        }
    };

    template<typename Domain>
    class Error : public Domain::Instruction {
    public:
        explicit Error(UnitFactory &factory) : Domain::Instruction(factory) {};
        static inline bool classof(const Error &) { return true; }
        static inline bool classof(const Error *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == ERROR){ return true; }
            return false;
        }

        virtual std::string msg() const = 0;

        InstructionClassEnum instructionClass() const override {
            return ERROR;
        }
    };

    template<typename Domain>
    class Expression : public Domain::Instruction {
    public:
        explicit Expression(UnitFactory &factory) : Domain::Instruction(factory) {};
        static inline bool classof(const Expression &) { return true; }
        static inline bool classof(const Expression *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() >= EXPRESSION_BEGIN && inst.instructionClass() <= EXPRESSION_END){ return true; }
            return false;
        }

        virtual Value* result() const = 0;
    };

    // Assign Instruction
    template<typename Domain>
    class Assignment : public Expression<Domain> {
    public:
        explicit Assignment(UnitFactory &factory) : Expression<Domain>(factory) {};
        static inline bool classof(const Assignment &) { return true; }
        static inline bool classof(const Assignment *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == ASSIGNMENT){ return true; }
            return false;
        }

        InstructionClassEnum instructionClass() const override {
            return ASSIGNMENT;
        }
    };

    //BinaryOpInstruction
    template<typename Domain>
    class BinaryOpExpr : public Expression<Domain> {
    public:
        explicit BinaryOpExpr(UnitFactory &factory) : Expression<Domain>(factory) {};
        static inline bool classof(const BinaryOpExpr &) { return true; }
        static inline bool classof(const BinaryOpExpr *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == BIN_OP){ return true; }
            return false;
        }

        virtual BinOp op() const = 0;
        InstructionClassEnum instructionClass() const override {
            return BIN_OP;
        }
    };

    //Unary Operation Instruction
    template<typename Domain>
    class  UnaryOpExpr : public Expression<Domain> {
    public:
        explicit UnaryOpExpr(UnitFactory &factory) : Expression<Domain>(factory) {};
        static inline bool classof(const UnaryOpExpr &) { return true; }
        static inline bool classof(const UnaryOpExpr *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == UN_OP){ return true; }
            return false;
        }

        virtual UnOp op() const = 0;
        virtual Value* operand() const = 0;

        InstructionClassEnum instructionClass() const override {
            return UN_OP;
        }
    };

    template<typename Domain>
    class CallExpr : public Expression<Domain> {
    public:
        explicit CallExpr(UnitFactory &factory) : Expression<Domain>(factory) {};
        static inline bool classof(const CallExpr &) { return true; }
        static inline bool classof(const CallExpr *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == CALL){ return true; }
            return false;
        }

        virtual bool hasReturn() const = 0;
        virtual Universe::Function* target() const = 0;
        virtual std::list<Value*> args() const = 0;

        InstructionClassEnum instructionClass() const override {
            return CALL;
        }
    };

    template<typename Domain>
    class CastExpr : public Expression<Domain> {
    public:
        explicit CastExpr(UnitFactory &factory) : Expression<Domain>(factory) {};
        static inline bool classof(const CastExpr &) { return true; }
        static inline bool classof(const CastExpr *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == CAST){ return true; }
            return false;
        }

        virtual Type *castTo() const = 0;

        InstructionClassEnum instructionClass() const override {
            return CAST;
        }
    };

    template<typename Domain>
    class TernaryExpr : public Expression<Domain> {
    public:
        explicit TernaryExpr(UnitFactory &factory) : Expression<Domain>(factory) {};
        static inline bool classof(const TernaryExpr &) { return true; }
        static inline bool classof(const TernaryExpr *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == TERNARY){ return true; }
            return false;
        }

        virtual Value *condition() const = 0;
        virtual Value *trueValue() const = 0;
        virtual Value *falseValue() const = 0;

        InstructionClassEnum instructionClass() const override {
            return TERNARY;
        }
    };

    template<typename Domain>
    class UnknownExpr : public Expression<Domain> {
    public:
        explicit UnknownExpr(UnitFactory &factory) : Expression<Domain>(factory) {};
        static inline bool classof(const UnknownExpr &) { return true; }
        static inline bool classof(const UnknownExpr *) { return true; }
        static inline bool classof(const typename Domain::Instruction *inst) { return classof(*inst); }
        static inline bool classof(const typename Domain::Instruction &inst) {
            if (inst.instructionClass() == UNKNOWN){ return true; }
            return false;
        }

        InstructionClassEnum instructionClass() const override {
            return UNKNOWN;
        }
    };

    /*class MemoryReadInstruction: public AssignInstruction{
    public:
        virtual InstructionVariable* getLHS() const = 0;
    };

    class MemoryWriteInstruction: public AssignInstruction{
    public:
        virtual MemoryRegion* getMemoryAddress() const = 0;
    };

    class AssignInst: public AssignInstruction{
    public:
        virtual InstructionVariable* getLHS() const = 0;
    };*/
}

#endif //VANGUARD_INSTRUCTIONCLASSES_H
