#ifndef INSTRUCTIONCLASSES_H
#define INSTRUCTIONCLASSES_H

#include "Instruction.h"
#include "Value.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include <string>
#include <list>

namespace vanguard{

    enum BinaryOpClass{Add, Sub, Mul, Div, Mod, Shl, Shr, And, Or, Xor, IFCmpInst};

    enum UnaryOpClass{Neg, Not};

    enum CastInstClass{AddrSpaceCast, BitCast, FPCasts, IntToPtr, PtrToInt, SExt, Trunc, ZExt};

    //BinaryOpInstruction
    class BinaryOpInstruction: public Instruction{
        public:
            explicit BinaryOpInstruction(const llvm::Instruction &inst);

            virtual unsigned getOpClass() = 0;

            virtual InstructionVariable* getLHS() = 0;
    };

    class BinaryOperator: public BinaryOpInstruction{
        public:
            explicit BinaryOperator(const llvm::Instruction &inst, const llvm::BinaryOperator &bop);

            BinaryOperator(const BinaryOperator&) = delete;

            unsigned getOpClass() override;

            InstructionVariable* getLHS() override;

            const llvm::BinaryOperator &unwrap() override;

        private:
            const llvm::BinaryOperator& binOp;
    };

    class CmpInst: public BinaryOpInstruction{
        public:
            explicit CmpInst(const llvm::Instruction &inst, const llvm::CmpInst &cmpinst);

            CmpInst(const CmpInst&) = delete;

            unsigned getOpClass() override;

            InstructionVariable* getLHS() override;

            const llvm::CmpInst &unwrap() override;

        private:
            const llvm::CmpInst& cmpInst;
    };

    // Branch Instruction
    class BranchInstruction: public Instruction{
        public:
            explicit BranchInstruction(const llvm::Instruction &inst);

            virtual Value* getCondition() = 0;

            virtual std::list<Block*> getSuccessors() = 0;
    };

    class BranchInst: public BranchInstruction{
        public:
            explicit BranchInst(const llvm::Instruction &inst, const llvm::BranchInst &brInst);

            BranchInst(const BranchInst&) = delete;

            bool isConditional();

            Value* getCondition() override;

            std::list<Block*> getSuccessors() override;

            const llvm::BranchInst &unwrap() override;

        private:
            const llvm::BranchInst& branchInst;
    };

    class IndirectBrInst: public BranchInstruction{
        public:
            explicit IndirectBrInst(const llvm::Instruction &inst, const llvm::IndirectBrInst &ibrInst);

            IndirectBrInst(const IndirectBrInst&) = delete;

            Value * getCondition() override;

            std::list<Block*> getSuccessors() override;

            const llvm::IndirectBrInst &unwrap() override;

        private:
            const llvm::IndirectBrInst& indirectBrInst;
    };

    class SwitchInst: public BranchInstruction{
        public:
            explicit SwitchInst(const llvm::Instruction &inst, const llvm::SwitchInst &swInst);

            SwitchInst(const SwitchInst&) = delete;

            Value* getCondition() override;

            std::list<Block*> getSuccessors() override;

            const llvm::SwitchInst &unwrap() override;

        private:
            const llvm::SwitchInst& switchInst;
    };

    //Unary Operation Instruciton
    class  UnaryOpInstruction: public Instruction{
        public:
            explicit UnaryOpInstruction(const llvm::Instruction &inst);

            virtual Value* getOperand() = 0;
    };

    class UnaryOperator: public UnaryOpInstruction{
        public:
            explicit UnaryOperator(const llvm::Instruction &inst, const llvm::UnaryOperator &uop);

            UnaryOperator(const UnaryOperator&) = delete;

            Value* getOperand() override;

            unsigned getOpClass();

            const llvm::UnaryOperator &unwrap() override;

        private:
            const llvm::UnaryOperator& unaryOperator;
    };

    class CastInst: public UnaryOpInstruction{
    public:
        explicit CastInst(const llvm::Instruction &inst, const llvm::CastInst &ci);

        CastInst(const CastInst&) = delete;

        unsigned getOpClass();

        Value* getOperand() override;

        const llvm::CastInst &unwrap() override;

    private:
        const llvm::CastInst& castInst;
    };

    class AllocaInst: public UnaryOpInstruction{
        public:
            explicit AllocaInst(const llvm::Instruction&, const llvm::AllocaInst&);

            AllocaInst(const AllocaInst&) = delete;

            Value* getOperand() override;

            const llvm::AllocaInst &unwrap() override;
        private:
            const llvm::AllocaInst &allocaInst;
    };

    class LoadInst: public UnaryOpInstruction{
    public:
        explicit LoadInst(const llvm::Instruction&, const llvm::LoadInst&);

        LoadInst(const LoadInst&) = delete;

        Value* getOperand() override;

        const llvm::LoadInst &unwrap() override;
    private:
        const llvm::LoadInst& loadInst;
    };

    class FreezeInst: public UnaryOpInstruction{
    public:
        explicit FreezeInst(const llvm::Instruction&, const llvm::FreezeInst&);

        FreezeInst(const FreezeInst&) = delete;

        Value* getOperand() override;

        const llvm::FreezeInst &unwrap() override;
    private:
        const llvm::FreezeInst& freezeInst;
    };

    //Call Instruction
    class CallInstruction: public Instruction{
        public:
            explicit CallInstruction(const llvm::Instruction &inst);

            virtual Function* getTarget() = 0;

            virtual std::list<Value*> getArgs() = 0;
    };

    class Call: public CallInstruction{
        public:
            explicit Call(const llvm::Instruction &inst, const llvm::CallBase &cb);

            Call(const Call&) = delete;

            Function* getTarget() override;

            std::list<Value*> getArgs() override;

            const llvm::CallBase &unwrap() override;

        private:
            const llvm::CallBase& call;
    };

    //Error Instruction
    class ErrorInstruction: public Instruction{
        public:
            explicit ErrorInstruction(const llvm::Instruction &inst);

            virtual std::string error() = 0;
    };

    class UnreachableInstruction: public ErrorInstruction{
        public:
            explicit UnreachableInstruction(const llvm::Instruction &inst, const llvm::UnreachableInst &ui);

            UnreachableInstruction(const UnreachableInstruction&) = delete;

            std::string error() override;

            const llvm::UnreachableInst &unwrap() override;

        private:
            const llvm::UnreachableInst& unreachableInstruction;
    };

    //Return Instruction
    class ReturnInstruction: public Instruction{
        public:
            explicit ReturnInstruction(const llvm::Instruction &inst);

            virtual bool returnsValue() = 0;

            virtual Value* returnValue() = 0;
    };

    class ReturnInst: public ReturnInstruction{
        public:
            explicit ReturnInst(const llvm::Instruction &inst, const llvm::ReturnInst &retInst);

            ReturnInst(const ReturnInst&) = delete;

            bool returnsValue() override;

            Value* returnValue() override;

            const llvm::ReturnInst &unwrap() override;

        private:
            const llvm::ReturnInst& returnInst;
    };

    // Assign Instruction
    class AssignInstruction: public Instruction{
        public:
            explicit AssignInstruction(const llvm::Instruction &inst);
    };

    class MemoryReadInstruction: public AssignInstruction{
        public:
            explicit MemoryReadInstruction(const llvm::Instruction &inst);

            virtual InstructionVariable* getLHS() = 0;
    };

    class SelectInst: public MemoryReadInstruction{
        public:
            explicit SelectInst(const llvm::Instruction &inst, const llvm::SelectInst &si);

            SelectInst(const SelectInst&) = delete;

            InstructionVariable* getLHS() override;

            const llvm::SelectInst &unwrap() override;

        private:
            const llvm::SelectInst& selectInst;
    };

    class ExtractElementInst: public MemoryReadInstruction{
        public:
            explicit ExtractElementInst(const llvm::Instruction &inst, const llvm::ExtractElementInst &eei);

            ExtractElementInst(const ExtractElementInst&) = delete;

            InstructionVariable* getLHS() override;

            const llvm::ExtractElementInst &unwrap() override;

        private:
            const llvm::ExtractElementInst& extractElementInst;
    };

    class MemoryWriteInstruction: public AssignInstruction{
        public:
            explicit MemoryWriteInstruction(const llvm::Instruction &inst);

            virtual MemoryAddress* getMemoryAddress() = 0;
    };

    class InsertValueInst: public MemoryWriteInstruction{
        public:
            explicit InsertValueInst(const llvm::Instruction &inst, const llvm::InsertValueInst &ivi);

            InsertValueInst(const InsertValueInst&) = delete;

            MemoryAddress* getMemoryAddress() override;

            const llvm::InsertValueInst &unwrap() override;

        private:
            const llvm::InsertValueInst& insertValueInst;
    };

    class InsertElementInst: public MemoryWriteInstruction{
        public:
            explicit InsertElementInst(const llvm::Instruction &inst, const llvm::InsertElementInst &iei);

            InsertElementInst(const InsertElementInst&) = delete;

            MemoryAddress* getMemoryAddress() override;

            const llvm::InsertElementInst &unwrap() override;

        private:
            const llvm::InsertElementInst& insertElementInst;
    };

    class StoreInst: public MemoryWriteInstruction{
        public:
            explicit StoreInst(const llvm::Instruction &inst, const llvm::StoreInst &si);

            StoreInst(const StoreInst&) = delete;

            MemoryAddress* getMemoryAddress() override;

            const llvm::StoreInst &unwrap() override;

        private:
            const llvm::StoreInst& storeInst;
    };

    class ShuffleVectorInst: public MemoryWriteInstruction{
        public:
            explicit ShuffleVectorInst(const llvm::Instruction &inst, const llvm::ShuffleVectorInst &svi);

            ShuffleVectorInst(const ShuffleVectorInst&) = delete;

            MemoryAddress* getMemoryAddress() override;

            const llvm::ShuffleVectorInst &unwrap() override;

        private:
            const llvm::ShuffleVectorInst& shuffleVectorInst;
    };

    class AssignInst: public AssignInstruction{
        public:
            explicit AssignInst(const llvm::Instruction &inst);

            virtual InstructionVariable* getLHS() = 0;
    };

    class PHINode: public AssignInst{
        public:
            explicit PHINode(const llvm::Instruction &inst, const llvm::PHINode &phin);

            PHINode(const PHINode&) = delete;

            InstructionVariable* getLHS() override;

            const llvm::PHINode &unwrap() override;

        private:
            const llvm::PHINode& phiNode;
    };

    class GetElementPtrInst: public AssignInst{
        public:
            explicit GetElementPtrInst(const llvm::Instruction &inst, const llvm::GetElementPtrInst &gepi);

            InstructionVariable* getLHS() override;

            const llvm::GetElementPtrInst &unwrap() override;

        private:
            const llvm::GetElementPtrInst& getElementPtrInst;
    };

}

#endif