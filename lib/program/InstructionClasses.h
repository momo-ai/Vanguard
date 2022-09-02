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
    class Branch : public Universe::Instruction {
    public:
        static inline bool classof(const Branch &) { return true; }
        static inline bool classof(const Branch *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
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
    class Return : public Universe::Instruction {
    public:
        static inline bool classof(const Return &) { return true; }
        static inline bool classof(const Return *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
            if (inst.instructionClass() == RETURN){ return true; }
            return false;
        }

        virtual bool returnsValue() const = 0;
        virtual Value* value() const = 0;

        InstructionClassEnum instructionClass() const override {
            return RETURN;
        }
    };

    class Error : public Universe::Instruction {
    public:
        static inline bool classof(const Error &) { return true; }
        static inline bool classof(const Error *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
            if (inst.instructionClass() == ERROR){ return true; }
            return false;
        }

        virtual std::string msg() const = 0;

        InstructionClassEnum instructionClass() const override {
            return ERROR;
        }
    };

    class Expression : public Universe::Instruction {
    public:
        static inline bool classof(const Expression &) { return true; }
        static inline bool classof(const Expression *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
            if (inst.instructionClass() >= EXPRESSION_BEGIN && inst.instructionClass() <= EXPRESSION_END){ return true; }
            return false;
        }

        virtual Value* result() const = 0;
    };

    // Assign Instruction
    class Assignment : public Expression {
    public:
        static inline bool classof(const Assignment &) { return true; }
        static inline bool classof(const Assignment *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
            if (inst.instructionClass() == ASSIGNMENT){ return true; }
            return false;
        }

        InstructionClassEnum instructionClass() const override {
            return ASSIGNMENT;
        }
    };

    //BinaryOpInstruction
    class BinaryOpExpr : public Expression {
    public:
        static inline bool classof(const BinaryOpExpr &) { return true; }
        static inline bool classof(const BinaryOpExpr *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
            if (inst.instructionClass() == BIN_OP){ return true; }
            return false;
        }

        virtual BinOp op() const = 0;
        InstructionClassEnum instructionClass() const override {
            return BIN_OP;
        }
    };

    //Unary Operation Instruction
    class  UnaryOpExpr : public Expression {
    public:
        static inline bool classof(const UnaryOpExpr &) { return true; }
        static inline bool classof(const UnaryOpExpr *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
            if (inst.instructionClass() == UN_OP){ return true; }
            return false;
        }

        virtual UnOp op() const = 0;
        virtual Value* operand() const = 0;

        InstructionClassEnum instructionClass() const override {
            return UN_OP;
        }
    };

    class CallExpr : public Expression {
    public:
        static inline bool classof(const CallExpr &) { return true; }
        static inline bool classof(const CallExpr *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
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

    class CastExpr : public Expression {
    public:
        static inline bool classof(const CastExpr &) { return true; }
        static inline bool classof(const CastExpr *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
            if (inst.instructionClass() == CAST){ return true; }
            return false;
        }

        virtual Type *castTo() const = 0;

        InstructionClassEnum instructionClass() const override {
            return CAST;
        }
    };

    class TernaryExpr : public Expression {
    public:
        static inline bool classof(const TernaryExpr &) { return true; }
        static inline bool classof(const TernaryExpr *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
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

    class UnknownExpr : public Expression {
    public:
        static inline bool classof(const UnknownExpr &) { return true; }
        static inline bool classof(const UnknownExpr *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
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
