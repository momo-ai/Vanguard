#ifndef INSTRUCTIONCLASSES_H
#define INSTRUCTIONCLASSES_H

#include "InstructionClasses.h"
#include "WrappedInstructionClass.h"

namespace vanguard{

    class BinaryIns: public WrappedInstructionClass<BinaryOpExpr, llvm::BinaryOperator> {
        public:
            explicit BinaryIns(UnitFactory &factory, const llvm::BinaryOperator &bop);
            BinaryIns(const BinaryIns&) = delete;

            BinOp op() const override;
            Value* result() const override;
    };

    class CmpIns: public WrappedInstructionClass<BinaryOpExpr, llvm::CmpInst> {
        public:
            explicit CmpIns(UnitFactory &factory, const llvm::CmpInst &cmpinst);
            CmpIns(const CmpIns&) = delete;

            BinOp op() const override;
            Value* result() const override;
    };

    class BranchIns: public WrappedInstructionClass<Branch, llvm::BranchInst> {
        public:
            explicit BranchIns(UnitFactory &factory, const llvm::BranchInst &brInst);
            BranchIns(const BranchIns&) = delete;

            bool isConditional() const override;
            Value* condition() const override;
            std::list<Universe::Block*> targets() const override;
    };

    class IndirectBrIns: public WrappedInstructionClass<Branch, llvm::IndirectBrInst> {
        public:
            explicit IndirectBrIns(UnitFactory &factory, const llvm::IndirectBrInst &ibrInst);
            IndirectBrIns(const IndirectBrIns&) = delete;

            bool isConditional() const override;
            Value * condition() const override;
            std::list<Universe::Block*> targets() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class SwitchIns: public WrappedInstructionClass<Branch, llvm::SwitchInst> {
        public:
            explicit SwitchIns(UnitFactory &factory, const llvm::SwitchInst &swInst);
            SwitchIns(const SwitchIns&) = delete;

            bool isConditional() const override;
            Value* condition() const override;
            std::list<Universe::Block*> targets() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class UnaryIns: public WrappedInstructionClass<UnaryOpExpr, llvm::UnaryOperator> {
        public:
            explicit UnaryIns(UnitFactory &factory, const llvm::UnaryOperator &uop);
            UnaryIns(const UnaryIns&) = delete;

            Value* result() const override;
            Value* operand() const override;
            UnOp op() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class CastIns: public WrappedInstructionClass<CastExpr, llvm::CastInst> {
    public:
        explicit CastIns(UnitFactory &factory, const llvm::CastInst &ci);
        CastIns(const CastIns&) = delete;

        Value* result() const override;
        Type *castTo() const override;

        //void accept(InstructionClassVisitor &v) const override;
    };

    class CallIns: public WrappedInstructionClass<CallExpr, llvm::CallBase> {
        public:
            explicit CallIns(UnitFactory &factory, const llvm::CallBase &cb);
            CallIns(const CallIns&) = delete;

            Value* result() const override;
            bool hasReturn() const override;
            Universe::Function* target() const override;
            std::list<Value*> args() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class UnreachableIns: public WrappedInstructionClass<Error, llvm::UnreachableInst> {
        public:
            explicit UnreachableIns(UnitFactory &factory, const llvm::UnreachableInst &ui);
            UnreachableIns(const UnreachableIns&) = delete;

            std::string msg() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class ReturnIns: public WrappedInstructionClass<Return, llvm::ReturnInst> {
        public:
            explicit ReturnIns(UnitFactory &factory, const llvm::ReturnInst &retInst);
            ReturnIns(const ReturnIns&) = delete;

            bool returnsValue() const override;
            Value* value() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class SelectIns: public WrappedInstructionClass<TernaryExpr, llvm::SelectInst> {
        public:
            explicit SelectIns(UnitFactory &factory, const llvm::SelectInst &si);
            SelectIns(const SelectIns&) = delete;

            Value* result() const override;
            Value *condition() const override;
            Value *trueValue() const override;
            Value *falseValue() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class ExtractElementIns: public WrappedInstructionClass<UnknownExpr, llvm::ExtractElementInst> {
    public:
        explicit ExtractElementIns(UnitFactory &factory, const llvm::ExtractElementInst &eei);
        ExtractElementIns(const ExtractElementIns&) = delete;

        Value* result() const override;

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
        explicit ExtractValueIns(UnitFactory &factory, const llvm::ExtractValueInst &evi);
        ExtractValueIns(const ExtractValueIns&) = delete;

        Value* result() const override;

//        Value *getAggregateOperand() const;
//
//        std::list<unsigned> getIndices() const;

        //void accept(InstructionClassVisitor &v) const override;
    };

    class LoadIns: public WrappedInstructionClass<UnknownExpr, llvm::LoadInst> {
    public:
        explicit LoadIns(UnitFactory &factory, const llvm::LoadInst&);
        LoadIns(const LoadIns&) = delete;

        Value* result() const override;

//        Value *getPointerOperand() const;
//
//        Type *getPointerOperandType() const;
//
//        unsigned getSize() const;

        //void accept(InstructionClassVisitor &v) const override;
    };

    class InsertValueIns: public WrappedInstructionClass<UnknownExpr, llvm::InsertValueInst> {
        public:
            explicit InsertValueIns(UnitFactory &factory, const llvm::InsertValueInst &ivi);
            InsertValueIns(const InsertValueIns&) = delete;

            Value* result() const override;

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
            explicit InsertElementIns(UnitFactory &factory, const llvm::InsertElementInst &iei);
            InsertElementIns(const InsertElementIns&) = delete;

            Value* result() const override;

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
            explicit StoreIns(UnitFactory &factory, const llvm::StoreInst &si);
            StoreIns(const StoreIns&) = delete;

            Value* result() const override;

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
            explicit ShuffleVectorIns(UnitFactory &factory, const llvm::ShuffleVectorInst &svi);
            ShuffleVectorIns(const ShuffleVectorIns&) = delete;

            Value* result() const override;

            //MemoryRegion* getMemoryAddress() const override;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class AllocaIns: public WrappedInstructionClass<UnknownExpr, llvm::AllocaInst> {
    public:
        explicit AllocaIns(UnitFactory &factory, const llvm::AllocaInst&);
        AllocaIns(const AllocaIns&) = delete;

        Value* result() const override;

//        Type *getAllocatedType() const;
//
//        MemoryRegion* getMemoryAddress() const override;

        //void accept(InstructionClassVisitor &v) const override;
    };

    class PHIIns: public WrappedInstructionClass<UnknownExpr, llvm::PHINode> {
        public:
            explicit PHIIns(UnitFactory &factory, const llvm::PHINode &phin);
            PHIIns(const PHIIns&) = delete;

            Value* result() const override;

//            unsigned getNumIncomingValues() const;
//
//            std::vector<Value *> getIncomingValues() const;
//
//            std::vector<Block *> getIncomingBlocks() const;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class GetElementPtrIns: public WrappedInstructionClass<UnknownExpr, llvm::GetElementPtrInst> {
        public:
            explicit GetElementPtrIns(UnitFactory &factory, const llvm::GetElementPtrInst &gepi);
            Value* result() const override;

//            Value *getPointerOperand() const;
//
//            Type *getPointerOperandType() const;

            //void accept(InstructionClassVisitor &v) const override;
    };

    class FreezeIns: public WrappedInstructionClass<UnknownExpr, llvm::FreezeInst> {
    public:
        explicit FreezeIns(UnitFactory &factory, const llvm::FreezeInst&);
        FreezeIns(const FreezeIns&) = delete;

        Value* result() const override;

        //void accept(InstructionClassVisitor &v) const override;
    };

}

#endif