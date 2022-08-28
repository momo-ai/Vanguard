#ifndef INSTRUCTIONCLASSES_H
#define INSTRUCTIONCLASSES_H

#include "InstructionClasses.h"
#include "WrappedInstructionClass.h"

namespace vanguard{

    class BinaryIns: public WrappedInstructionClass<BinaryOpExpr, llvm::BinaryOperator> {
        public:
            explicit BinaryIns(const llvm::BinaryOperator &bop);
            BinaryIns(const BinaryIns&) = delete;

            BinOp op() const override;
            Variable* result() const override;
    };

    class CmpIns: public WrappedInstructionClass<BinaryOpExpr, llvm::CmpInst> {
        public:
            explicit CmpIns(const llvm::CmpInst &cmpinst);
            CmpIns(const CmpIns&) = delete;

            BinOp op() const override;
            Variable* result() const override;
    };

    class BranchIns: public WrappedInstructionClass<Branch, llvm::BranchInst> {
        public:
            explicit BranchIns(const llvm::BranchInst &brInst);
            BranchIns(const BranchIns&) = delete;

            bool isConditional() const override;
            Value* condition() const override;
            std::list<Block*> targets() const override;
    };

    class IndirectBrIns: public WrappedInstructionClass<Branch, llvm::IndirectBrInst> {
        public:
            explicit IndirectBrIns(const llvm::IndirectBrInst &ibrInst);
            IndirectBrIns(const IndirectBrIns&) = delete;

            bool isConditional() const override;
            Value * condition() const override;
            std::list<Block*> targets() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class SwitchIns: public WrappedInstructionClass<Branch, llvm::SwitchInst> {
        public:
            explicit SwitchIns(const llvm::SwitchInst &swInst);
            SwitchIns(const SwitchIns&) = delete;

            bool isConditional() const override;
            Value* condition() const override;
            std::list<Block*> targets() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class UnaryIns: public WrappedInstructionClass<UnaryOpExpr, llvm::UnaryOperator> {
        public:
            explicit UnaryIns(const llvm::UnaryOperator &uop);
            UnaryIns(const UnaryIns&) = delete;

            Variable* result() const override;
            Value* operand() const override;
            UnOp op() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class CastIns: public WrappedInstructionClass<CastExpr, llvm::CastInst> {
    public:
        explicit CastIns(const llvm::CastInst &ci);
        CastIns(const CastIns&) = delete;

        Variable* result() const override;
        Type *castTo() const override;

        //void accept(InstructionClassVisitor &v) const override;
    };

    class CallIns: public WrappedInstructionClass<CallExpr, llvm::CallBase> {
        public:
            explicit CallIns(const llvm::CallBase &cb);
            CallIns(const CallIns&) = delete;

            Variable* result() const override;
            bool hasReturn() const override;
            Function* target() const override;
            std::list<Value*> args() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class UnreachableIns: public WrappedInstructionClass<Error, llvm::UnreachableInst> {
        public:
            explicit UnreachableIns(const llvm::UnreachableInst &ui);
            UnreachableIns(const UnreachableIns&) = delete;

            std::string msg() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class ReturnIns: public WrappedInstructionClass<Return, llvm::ReturnInst> {
        public:
            explicit ReturnIns(const llvm::ReturnInst &retInst);
            ReturnIns(const ReturnIns&) = delete;

            bool returnsValue() const override;
            Value* value() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class SelectIns: public WrappedInstructionClass<TernaryExpr, llvm::SelectInst> {
        public:
            explicit SelectIns(const llvm::SelectInst &si);
            SelectIns(const SelectIns&) = delete;

            Variable* result() const override;
            Value *condition() const override;
            Value *trueValue() const override;
            Value *falseValue() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class ExtractElementIns: public WrappedInstructionClass<UnknownExpr, llvm::ExtractElementInst> {
    public:
        explicit ExtractElementIns(const llvm::ExtractElementInst &eei);
        ExtractElementIns(const ExtractElementIns&) = delete;

        Variable* result() const override;

//        Value* operand(unsigned i) const override;
//        unsigned numOperands() const override;
    private:
//        MemoryRegion *region;

        //Value *getVectorOperand() const;

        //Value *getIndexOperand() const;

        //void accept(InstructionClassVisitor &v) const override;
    };

    //https://llvm.org/docs/LangRef.html#extractvalue-instruction
    class ExtractValueIns: public WrappedInstructionClass<UnknownExpr, llvm::ExtractValueInst> {
    public:
        explicit ExtractValueIns(const llvm::ExtractValueInst &evi);
        ExtractValueIns(const ExtractValueIns&) = delete;

        Variable* result() const override;

//        Value *getAggregateOperand() const;
//
//        std::list<unsigned> getIndices() const;

        //void accept(InstructionClassVisitor &v) const override;
    };

    class LoadIns: public WrappedInstructionClass<UnknownExpr, llvm::LoadInst> {
    public:
        explicit LoadIns(const llvm::LoadInst&);
        LoadIns(const LoadIns&) = delete;

        Variable* result() const override;

//        Value *getPointerOperand() const;
//
//        Type *getPointerOperandType() const;
//
//        unsigned getSize() const;

        //void accept(InstructionClassVisitor &v) const override;
    };

    class InsertValueIns: public WrappedInstructionClass<UnknownExpr, llvm::InsertValueInst> {
        public:
            explicit InsertValueIns(const llvm::InsertValueInst &ivi);
            InsertValueIns(const InsertValueIns&) = delete;

            Variable* result() const override;

//            Value *getAggregateOperand() const;
//
//            Value *getInsertedValueOperand() const;
//
//            std::list<unsigned> getIndices() const;
//
//            MemoryRegion* getMemoryAddress() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class InsertElementIns: public WrappedInstructionClass<UnknownExpr, llvm::InsertElementInst> {
        public:
            explicit InsertElementIns(const llvm::InsertElementInst &iei);
            InsertElementIns(const InsertElementIns&) = delete;

            Variable* result() const override;

//            Value *getVector() const;
//
//            Value *getInsertedElement() const;
//
//            Value *getIndex() const;
//
//            MemoryRegion* getMemoryAddress() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class StoreIns: public WrappedInstructionClass<UnknownExpr, llvm::StoreInst> {
        public:
            explicit StoreIns(const llvm::StoreInst &si);
            StoreIns(const StoreIns&) = delete;

            Variable* result() const override;

//            Value *getPointerOperand() const;
//
//            Value *getValueOperand() const;
//
//            Type *getPointerOperandType() const;
//
//            unsigned getSize() const;
//
//            MemoryRegion* getMemoryAddress() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class ShuffleVectorIns: public WrappedInstructionClass<UnknownExpr, llvm::ShuffleVectorInst> {
        public:
            explicit ShuffleVectorIns(const llvm::ShuffleVectorInst &svi);
            ShuffleVectorIns(const ShuffleVectorIns&) = delete;

            Variable* result() const override;

            //MemoryRegion* getMemoryAddress() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class AllocaIns: public WrappedInstructionClass<UnknownExpr, llvm::AllocaInst> {
    public:
        explicit AllocaIns(const llvm::AllocaInst&);
        AllocaIns(const AllocaIns&) = delete;

        Variable* result() const override;

//        Type *getAllocatedType() const;
//
//        MemoryRegion* getMemoryAddress() const override;

        //void accept(InstructionClassVisitor &v) const override;
    };

    class PHIIns: public WrappedInstructionClass<UnknownExpr, llvm::PHINode> {
        public:
            explicit PHIIns(const llvm::PHINode &phin);
            PHIIns(const PHIIns&) = delete;

            Variable* result() const override;

//            unsigned getNumIncomingValues() const;
//
//            std::vector<Value *> getIncomingValues() const;
//
//            std::vector<Block *> getIncomingBlocks() const;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class GetElementPtrIns: public WrappedInstructionClass<UnknownExpr, llvm::GetElementPtrInst> {
        public:
            explicit GetElementPtrIns(const llvm::GetElementPtrInst &gepi);
            Variable* result() const override;

//            Value *getPointerOperand() const;
//
//            Type *getPointerOperandType() const;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class FreezeIns: public WrappedInstructionClass<UnknownExpr, llvm::FreezeInst> {
    public:
        explicit FreezeIns(const llvm::FreezeInst&);
        FreezeIns(const FreezeIns&) = delete;

        Variable* result() const override;

        //void accept(InstructionClassVisitor &v) const override;
    };

}

#endif