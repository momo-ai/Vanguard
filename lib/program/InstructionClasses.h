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

    //BinaryOpInstruction
    class BinaryOpInstruction: public Instruction{
        public:
            BinaryOpInstruction();

            virtual unsigned getOpClass() = 0;

            virtual InstructionVariable* getLHS() = 0;
    };

    class BinaryOperator: public BinaryOpInstruction{
        public:
            explicit BinaryOperator(const llvm::BinaryOperator&);

            BinaryOperator(const BinaryOperator&) = delete;

            unsigned getOpClass() override;

            InstructionVariable* getLHS() override;

            const llvm::BinaryOperator* unwrap();

        private:
            const llvm::BinaryOperator& binOp;
    };

    class CmpInst: public BinaryOpInstruction{
        public:
            explicit CmpInst(const llvm::CmpInst&);

            CmpInst(const CmpInst&) = delete;

            unsigned getOpClass() override;

            InstructionVariable* getLHS() override;

            const llvm::CmpInst* unwrap();

        private:
            const llvm::CmpInst& cmpInst;
    };

    // Branch Instruction
    class BranchInstruction: public Instruction{
        public:
            BranchInstruction();

            virtual Value* getCondition() = 0;

            virtual std::list<Block*> getSuccessors() = 0;
    };

    class BranchInst: public BranchInstruction{
        public:
            explicit BranchInst(const llvm::BranchInst&);

            BranchInst(const BranchInst&) = delete;

            bool isConditional();

            Value* getCondition() override;

            std::list<Block*> getSuccessors() override;

            const llvm::BranchInst* unwrap();

        private:
            const llvm::BranchInst& branchInst;
    };

    class IndirectBrInst: public BranchInstruction{
        public:
            explicit IndirectBrInst(const llvm::IndirectBrInst&);

            IndirectBrInst(const IndirectBrInst&) = delete;

            Value * getCondition() override;

            std::list<Block*> getSuccessors() override;

            const llvm::IndirectBrInst* unwrap();
        
        private:
            const llvm::IndirectBrInst& indirectBrInst;
    };

    class SwitchInst: public BranchInstruction{
        public:
            explicit SwitchInst(const llvm::SwitchInst&);

            SwitchInst(const SwitchInst&) = delete;

            Value* getCondition() override;

            std::list<Block*> getSuccessors() override;

            const llvm::SwitchInst* unwrap();
        
        private:
            const llvm::SwitchInst& switchInst;
    };

    //Unary Operation Instruciton
    class  UnaryOpInstruction: public Instruction{
        public:
            UnaryOpInstruction();
            
            virtual Value* getOperand() = 0;

            virtual unsigned getOpClass() = 0;
    };

    class UnaryOperator: public UnaryOpInstruction{
        public:
            explicit UnaryOperator(const llvm::UnaryOperator&);

            UnaryOperator(const UnaryOperator&) = delete;

            Value* getOperand();

            unsigned getOpClass();

            const llvm::UnaryOperator* unwrap();
        
        private:
            const llvm::UnaryOperator& unaryOperator;
    };

    //Call Instruction
    class CallInstruction: public Instruction{
        public:
            CallInstruction();

            virtual Function* getTarget();

            virtual std::list<Value*> getArgs();
    };

    class Call: public CallInstruction{
        public:
            explicit Call(const llvm::CallBase&);

            Call(const Call&) = delete;

            Function* getTarget() override;

            std::list<Value*> getArgs() override;

            const llvm::CallBase* unwrap();

        private:
            const llvm::CallBase& call;
    };

    //Error Instruction
    class ErrorInstruction: public Instruction{
        public:
            ErrorInstruction();

            virtual std::string error();
    };

    class UnreachableInstruction: public ErrorInstruction{
        public:
            explicit UnreachableInstruction(const llvm::UnreachableInst&);

            UnreachableInstruction(const UnreachableInstruction&) = delete;

            std::string error() override;

            const llvm::UnreachableInst* unwrap();
        
        private:
            const llvm::UnreachableInst& unreachableInstruction;
    };

    //Return Instruction
    class ReturnInstruction: public Instruction{
        public:
            ReturnInstruction();

            virtual bool returnsValue();

            virtual Value* returnValue();
    };

    class ReturnInst: public ReturnInstruction{
        public:
            explicit ReturnInst(const llvm::ReturnInst&);

            ReturnInst(const ReturnInst&) = delete;

            bool returnsValue() override;

            Value* returnValue() override;

            const llvm::ReturnInst* unwrap();

        private:
            const llvm::ReturnInst& returnInst;
    };

    // Assign Instruction
    class AssignInstruction: public Instruction{
        public:
            AssignInstruction();
    };

    class MemoryReadInstruction: public AssignInstruction{
        public:
            MemoryReadInstruction();

            virtual InstructionVariable* getLHS() = 0;
    };

    class SelectInst: public MemoryReadInstruction{
        public:
            explicit SelectInst(const llvm::SelectInst&);

            SelectInst(const SelectInst&) = delete;

            InstructionVariable* getLHS() override;

            const llvm::SelectInst* unwrap();

        private:
            const llvm::SelectInst& selectInst;
    };

    class ExtractElementInst: public MemoryReadInstruction{
        public:
            explicit ExtractElementInst(const llvm::ExtractElementInst&);

            ExtractElementInst(const ExtractElementInst&) = delete;

            InstructionVariable* getLHS() override;

            const llvm::ExtractElementInst* unwrap();
        
        private:
            const llvm::ExtractElementInst& extractElementInst;
    };

    class MemoryWriteInstruction: public AssignInstruction{
        public:
            MemoryWriteInstruction();

            virtual MemoryAddress* getMemoryAddress() = 0;
    };

    class InsertValueInst: public MemoryWriteInstruction{
        public:
            explicit InsertValueInst(const llvm::InsertValueInst&);

            InsertValueInst(const InsertValueInst&) = delete;

            MemoryAddress* getMemoryAddress() override;

            const llvm::InsertValueInst* unwrap();
        
        private:
            const llvm::InsertValueInst& insertValueInst;
    };

    class InsertElementInst: public MemoryWriteInstruction{
        public:
            explicit InsertElementInst(const llvm::InsertElementInst&);

            InsertElementInst(const InsertElementInst&) = delete;

            MemoryAddress* getMemoryAddress() override;

            const llvm::InsertElementInst* unwrap();
        
        private:
            const llvm::InsertElementInst& insertElementInst;
    };

    class StoreInst: public MemoryWriteInstruction{
        public:
            explicit StoreInst(const llvm::StoreInst&);

            StoreInst(const StoreInst&) = delete;

            MemoryAddress* getMemoryAddress() override;

            const llvm::StoreInst* unwrap();
        
        private:
            const llvm::StoreInst& storeInst;
    };

    class ShuffleVectorInst: public MemoryWriteInstruction{
        public:
            explicit ShuffleVectorInst(const llvm::ShuffleVectorInst&);

            ShuffleVectorInst(const ShuffleVectorInst&) = delete;

            MemoryAddress* getMemoryAddress() override;

            const llvm::ShuffleVectorInst* unwrap();
        
        private:
            const llvm::ShuffleVectorInst& shuffleVectorInst;
    };

    class AssignInst: public AssignInstruction{
        public:
            AssignInst();

            virtual InstructionVariable* getLHS() = 0;
    };

    class PHINode: public AssignInst{
        public:
            explicit PHINode(const llvm::PHINode&);

            PHINode(const PHINode&) = delete;

            InstructionVariable* getLHS() override;

            const llvm::PHINode* unwrap();
        
        private:
            const llvm::PHINode& phiNode;
    };

    class GetElementPtrInst: public AssignInst{
        public:
            explicit GetElementPtrInst(const llvm::GetElementPtrInst&);
            
            InstructionVariable* getLHS() override;

            const llvm::GetElementPtrInst* unwrap();

        private:
            const llvm::GetElementPtrInst& getElemenPtrInst;
    };
}

#endif