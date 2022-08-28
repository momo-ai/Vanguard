#ifndef VANGUARD_PROGRAM_INSTRUCTION_H
#define VANGUARD_PROGRAM_INSTRUCTION_H

#include "Function.h"

namespace vanguard{

    enum InstructionClassEnum {
        BRANCH,
        RETURN,
        ERROR,
        EXPRESSION_BEGIN,
        BIN_OP = EXPRESSION_BEGIN,
        UN_OP,
        CALL,
        CAST,
        TERNARY,
        ASSIGNMENT,
        UNKNOWN,
        EXPRESSION_END = UNKNOWN
    };

    class InstructionClassVisitor;
    class Instruction{

    public:
        static inline bool classof(const Instruction &) { return true; }
        static inline bool classof(const Instruction *) { return true; }

        virtual InstructionClassEnum instructionClass() const = 0;

        virtual std::string name() const = 0;

        virtual Block* parent() const = 0;

        virtual bool mayReadOrWriteToMemory() const = 0;

        virtual bool willReturn() const = 0;

        virtual Instruction * getSuccessor() const = 0;

        virtual std::list<Instruction*> getAllSuccessors() const = 0;

        virtual Value* operand(unsigned i) const = 0;

        virtual unsigned numOperands() const = 0;

        virtual const llvm::Instruction &unwrap() const = 0;

        virtual void accept(InstructionClassVisitor &v) const = 0;

    };

}

#endif