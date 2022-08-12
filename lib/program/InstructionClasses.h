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
            BinaryOperator(llvm::BinaryOperator&);

            unsigned getOpClass() override;

            InstructionVariable* getLHS() override;

            llvm::BinaryOperator* unwrap();

        private:
            llvm::BinaryOperator& binOp;
    };

    class CmpInst: public BinaryOpInstruction{
        public:
            CmpInst(llvm::CmpInst&);

            unsigned getOpClass() override;

            InstructionVariable* getLHS() override;

            llvm::CmpInst* unwrap();

        private:
            llvm::CmpInst& cmpInst;
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
            BranchInst(llvm::BranchInst&);

            bool isConditional();

            Value* getCondition() override;

            std::list<Block*> getSuccessors() override;

            llvm::BranchInst* unwrap();

        private:
            llvm::BranchInst& branchInst;
    };

    class IndirectBrInst: public BranchInstruction{
        public:
            IndirectBrInst(llvm::IndirectBrInst&);

            Value * getCondition() override;

            std::list<Block*> getSuccessors() override;

            llvm::IndirectBrInst* unwrap();
        
        private:
            llvm::IndirectBrInst& indirectBrInst;
    };

    class SwitchInst: public BranchInstruction{
        public:
            SwitchInst(llvm::SwitchInst&);

            Value* getCondition() override;

            std::list<Block*> getSuccessors() override;

            llvm::SwitchInst* unwrap();
        
        private:
            llvm::SwitchInst& switchInst;
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
            UnaryOperator(llvm::UnaryOperator&);

            Value* getOperand();

            unsigned getOpClass();

            llvm::UnaryOperator* unwrap();
        
        private:
            llvm::UnaryOperator& unaryOperator;
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
            Call(llvm::CallBase&);

            Function* getTarget() override;

            std::list<Value*> getArgs();

            llvm::CallBase* unwrap();

        private:
            llvm::CallBase& call;
    };

    //Error Instruction
    class ErrorInstruction: public Instruction{
        public:
            ErrorInstruction();

            virtual std::string error();
    };

    class UnreachableInstruction: public ErrorInstruction{
        public:
            UnreachableInstruction(llvm::UnreachableInst&);

            std::string error() override;

            llvm::UnreachableInst* unwrap();
        
        private:
            llvm::UnreachableInst& unreachableInstruction;
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
            ReturnInst(llvm::ReturnInst&);

            bool returnsValue() override;

            Value* returnValue() override;

            llvm::ReturnInst* unwrap();

        private:
            llvm::ReturnInst& returnInst;
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
            SelectInst(llvm::SelectInst&);

            InstructionVariable* getLHS() override;

            llvm::SelectInst* unwrap();

        private:
            llvm::SelectInst& selectInst;
    };

    class ExtractElementInst: public MemoryReadInstruction{
        public:
            ExtractElementInst(llvm::ExtractElementInst&);

            InstructionVariable* getLHS() override;

            llvm::ExtractElementInst* unwrap();
        
        private:
            llvm::ExtractElementInst& extractElementInst;
    };

    class MemoryWriteInstruction: public AssignInstruction{
        public:
            MemoryWriteInstruction();

            virtual MemoryAddress* getMemoryAddress() = 0;
    };

    class InsertValueInst: public MemoryWriteInstruction{
        public:
            InsertValueInst(llvm::InsertValueInst&);

            MemoryAddress* getMemoryAddress() override;

            llvm::InsertValueInst* unwrap();
        
        private:
            llvm::InsertValueInst& insertValueInst;
    };

    class InsertElementInst: public MemoryWriteInstruction{
        public:
            InsertElementInst(llvm::InsertElementInst&);

            MemoryAddress* getMemoryAddress() override;

            llvm::InsertElementInst* unwrap();
        
        private:
            llvm::InsertElementInst& insertElementInst;
    };

    class StoreInst: public MemoryWriteInstruction{
        public:
            StoreInst(llvm::StoreInst&);

            MemoryAddress* getMemoryAddress() override;

            llvm::StoreInst* unwrap();
        
        private:
            llvm::StoreInst& storeInst;
    };

    class ShuffleVectorInst: public MemoryWriteInstruction{
        public:
            ShuffleVectorInst(llvm::ShuffleVectorInst&);

            MemoryAddress* getMemoryAddress() override;

            llvm::ShuffleVectorInst* unwrap();
        
        private:
            llvm::ShuffleVectorInst& shuffleVectorInst;
    };

    class AssignInst: public AssignInstruction{
        public:
            AssignInst();

            virtual InstructionVariable* getLHS() = 0;
    };

    class PHINode: public AssignInst{
        public:
            PHINode(llvm::PHINode&);

            InstructionVariable* getLHS() override;

            llvm::PHINode* unwrap();
        
        private:
            llvm::PHINode& phiNode;
    };

    class GetElementPtrInst: public AssignInst{
        public:
            GetElementPtrInst(llvm::GetElementPtrInst&);
            
            InstructionVariable* getLHS() override;

            llvm::GetElementPtrInst* unwrap();

        private:
            llvm::GetElementPtrInst& getElemenPtrInst;
    };
}

#endif