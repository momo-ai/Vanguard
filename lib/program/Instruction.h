#ifndef VANGUARD_PROGRAM_INSTRUCTION_H
#define VANGUARD_PROGRAM_INSTRUCTION_H

#include "Function.h"
#include <unordered_set>
#include "llvm/IR/Instruction.h"

namespace vanguard{

    enum InstructionClassEnum {
        BIN_OP_INSTRUCTION_BEGIN,
        BINARY_OPERATOR = BIN_OP_INSTRUCTION_BEGIN,
        CMP_INST,
        BIN_OP_INSTRUCTION_END = CMP_INST,
        BRANCH_INSTRUCTION_BEGIN,
        BRANCH_INST = BRANCH_INSTRUCTION_BEGIN,
        INDIRECT_BR_INST,
        SWITCH_INST,
        BRANCH_INSTRUCTION_END = SWITCH_INST,
        UNARY_OP_INSTRUCTION_BEGIN,
        UNARY_OPERATOR = UNARY_OP_INSTRUCTION_BEGIN,
        CAST_INST,
        UNARY_OP_INSTRUCTION_END = CAST_INST,
        CALL_INSTRUCTION_BEGIN,
        CALL = CALL_INSTRUCTION_BEGIN,
        CALL_INSTRUCTION_END = CALL,
        ERROR_INSTRUCTION_BEGIN,
        UNREACHABLE_INSTRUCTION = ERROR_INSTRUCTION_BEGIN,
        RETURN_INST,
        ERROR_INSTRUCTION_END = RETURN_INST,
        ASSIGN_INSTRUCTION_BEGIN,
        MEMORY_READ_INSTRUCTION_BEGIN = ASSIGN_INSTRUCTION_BEGIN,
        SELECT_INST = MEMORY_READ_INSTRUCTION_BEGIN,
        EXTRACT_ELEMENT_INST,
        EXTRACT_VALUE_INST,
        LOAD_INST,
        MEMORY_READ_INSTRUCTION_END = LOAD_INST,
        ASSIGN_INSTRUCTION_END = MEMORY_READ_INSTRUCTION_END,
        MEMORY_WRITE_INSTRUCTION_BEGIN,
        INSERT_VALUE_INST = MEMORY_WRITE_INSTRUCTION_BEGIN,
        INSERT_ELEMENT_INST,
        STORE_INST,
        SHUFFLE_VECTOR_INST,
        ALLOCA_INST,
        MEMORY_WRITE_INSTRUCTION_END = ALLOCA_INST,
        ASSIGN_INST_BEGIN,
        PHI_NODE = ASSIGN_INST_BEGIN,
        GET_ELEMENT_PTR_INST,
        FREEZE_INST
    };

    class Instruction{
    private:
        InstructionClassEnum instructionClassEnum;

    public:
        explicit Instruction(InstructionClassEnum it): instructionClassEnum(it){}

        static inline bool classof(const Instruction &) { return true; }
        static inline bool classof(const Instruction *) { return true; }

        InstructionClassEnum getInstructionClassEnum() const{
            return instructionClassEnum;
        }

        virtual std::string getName() = 0;

        virtual Block* getBlock() = 0;

        virtual std::string getInstructionType() = 0;

        virtual bool mayReadOrWriteToMemory() = 0;

        virtual bool willReturn() = 0;

        virtual Instruction * getSuccessor() = 0;

        virtual std::unordered_set<Instruction*> getAllSuccessors() = 0;

        virtual Value* getOperand(unsigned i) = 0;

        virtual unsigned getNumOperands() = 0;

        virtual const llvm::Instruction &unwrap() = 0;

    };

}

#endif