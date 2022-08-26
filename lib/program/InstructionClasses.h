#ifndef INSTRUCTIONCLASSES_H
#define INSTRUCTIONCLASSES_H

#include "Instruction.h"
#include "Value.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include "LLVMtoVanguard.h"
#include <string>
#include <list>

namespace vanguard{

    template<typename T> class InstructionClass: public Instruction{
        static_assert(std::is_base_of<llvm::Instruction, T>::value, "T must inherit from instruction.");
    public:

        explicit InstructionClass(InstructionClassEnum ice, const T &inst): Instruction(ice), instructionClassEnum(ice), instr(inst){
            instruction = llvm::dyn_cast<llvm::Instruction>(&instr);
        }

        std::string getName() const override {
            return instruction->getName().str();
        }

        Block* getBlock() const override{
            auto &llvmToVanguard = LLVMtoVanguard::getInstance();
            return llvmToVanguard.translateBlock(instruction->getParent());
        }

        std::string getInstructionType() const override{
            return (std::string)instruction->getOpcodeName();
        }

        bool mayReadOrWriteToMemory() const override{
            return instruction->mayReadOrWriteMemory();
        }

        bool willReturn() const override{
            return instruction->willReturn();
        }

        Instruction* getSuccessor() const override{
            if (instruction->isTerminator()){
                return nullptr;
            }
            auto nextInst = instruction->getNextNonDebugInstruction();
            if (nextInst == nullptr){
                return nullptr;
            }
            else{
                auto &llvmToVanguard = LLVMtoVanguard::getInstance();
                return llvmToVanguard.translateInstruction(nextInst);
            }
        }

        std::list<Instruction*> getAllSuccessors() const override{
            std::list<Instruction *> allSuccessors = {};
            if (instruction->isTerminator()) {
                auto &llvmToVanguard = LLVMtoVanguard::getInstance();
                int numSuccessors = instruction->getNumSuccessors();
                for (int i = 0; i < numSuccessors; i++) {
                    allSuccessors.push_back(llvmToVanguard.translateBlock(instruction->getSuccessor(i))->getInstructionsList().front());
                }
                return allSuccessors;
            }
            else{
                return allSuccessors;
            }
        }

        Value* getOperand(unsigned i) const override{
            auto &llvmToVanguard = LLVMtoVanguard::getInstance();
            return llvmToVanguard.translateValue(instruction->getOperand(i));
        }

        unsigned getNumOperands() const override{
            return instruction->getNumOperands();
        }

        const llvm::Instruction &unwrap()  const override{
            return *instruction;
        }

    private:
        InstructionClassEnum  instructionClassEnum;
        const llvm::Instruction *instruction;
        const T &instr;
    };

    enum BinaryOpClass{Add, Sub, Mul, Div, Mod, Shl, Shr, And, Or, Xor, IFCmpInst};

    enum UnaryOpClass{Neg, Not};

    enum CastInstClass{AddrSpaceCast, BitCast, FPCasts, IntToPtr, PtrToInt, SExt, Trunc, ZExt};

    //BinaryOpInstruction
    class BinaryOpInstruction{
        public:
            virtual unsigned getOpClass() const = 0;

            virtual InstructionVariable* getLHS() const = 0;
    };

    class BinaryOperator: public InstructionClass<llvm::BinaryOperator>, public BinaryOpInstruction{
        public:
            explicit BinaryOperator(const llvm::BinaryOperator &bop);

            static inline bool classof(const BinaryOperator &) { return true; }
            static inline bool classof(const BinaryOperator *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == BINARY_OPERATOR){ return true; }
                return false;
            }

            BinaryOperator(const BinaryOperator&) = delete;

            unsigned getOpClass() const override;

            InstructionVariable* getLHS() const override;

            const llvm::BinaryOperator &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::BinaryOperator& binOp;
    };

    class CmpInst: public InstructionClass<llvm::CmpInst>, public BinaryOpInstruction{
        public:
            explicit CmpInst(const llvm::CmpInst &cmpinst);

            static inline bool classof(const CmpInst &) { return true; }
            static inline bool classof(const CmpInst *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == CMP_INST){ return true; }
                return false;
            }

            CmpInst(const CmpInst&) = delete;

            unsigned getOpClass() const override;

            InstructionVariable* getLHS() const override;

            const llvm::CmpInst &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::CmpInst& cmpInst;
    };

    // Branch Instruction
    class BranchInstruction{
        public:
            virtual Value* getCondition() const = 0;

            virtual std::list<Block*> getSuccessors() const = 0;
    };

    class BranchInst: public InstructionClass<llvm::BranchInst>, public BranchInstruction{
        public:
            explicit BranchInst( const llvm::BranchInst &brInst);

            static inline bool classof(const BranchInst &) { return true; }
            static inline bool classof(const BranchInst *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == BRANCH_INST){ return true; }
                return false;
            }

            BranchInst(const BranchInst&) = delete;

            bool isConditional() const;

            Value* getCondition() const override;

            std::list<Block*> getSuccessors() const override;

            const llvm::BranchInst &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::BranchInst& branchInst;
    };

    class IndirectBrInst: public InstructionClass<llvm::IndirectBrInst>, public BranchInstruction{
        public:
            explicit IndirectBrInst(const llvm::IndirectBrInst &ibrInst);

            static inline bool classof(const IndirectBrInst &) { return true; }
            static inline bool classof(const IndirectBrInst *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == INDIRECT_BR_INST){ return true; }
                return false;
            }

            IndirectBrInst(const IndirectBrInst&) = delete;

            Value * getCondition() const override;

            std::list<Block*> getSuccessors() const override;

            const llvm::IndirectBrInst &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::IndirectBrInst& indirectBrInst;
    };

    class SwitchInst: public InstructionClass<llvm::SwitchInst>, public BranchInstruction{
        public:
            explicit SwitchInst(const llvm::SwitchInst &swInst);

            static inline bool classof(const SwitchInst &) { return true; }
            static inline bool classof(const SwitchInst *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == SWITCH_INST){ return true; }
                return false;
            }

            SwitchInst(const SwitchInst&) = delete;

            Value* getCondition() const override;

            std::list<Block*> getSuccessors() const override;

            const llvm::SwitchInst &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::SwitchInst& switchInst;
    };

    //Unary Operation Instruction
    class  UnaryOpInstruction{
        public:
            virtual Value* getUnaryOperand() const = 0;
    };

    class UnaryOperator: public InstructionClass<llvm::UnaryOperator>, public UnaryOpInstruction{
        public:
            explicit UnaryOperator(const llvm::UnaryOperator &uop);

            static inline bool classof(const UnaryOperator &) { return true; }
            static inline bool classof(const UnaryOperator *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == UNARY_OPERATOR){ return true; }
                return false;
            }

            UnaryOperator(const UnaryOperator&) = delete;

            Value* getUnaryOperand() const override;

            unsigned getOpClass() const;

            const llvm::UnaryOperator &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::UnaryOperator& unaryOperator;
    };

    class CastInst: public InstructionClass<llvm::CastInst>, public UnaryOpInstruction{
    public:
        explicit CastInst(const llvm::CastInst &ci);

        static inline bool classof(const CastInst &) { return true; }
        static inline bool classof(const CastInst *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
            if (inst.getInstructionClassEnum() == CAST_INST){ return true; }
            return false;
        }

        CastInst(const CastInst&) = delete;

        unsigned getOpClass() const;

        Value* getUnaryOperand() const override;

        Type* getSrcType() const;

        Type* getDestType() const;

        const llvm::CastInst &unwrap() const override;

        void accept(InstructionClassVisitor &v) const override;

    private:
        const llvm::CastInst& castInst;
    };

    //Call Instruction
    class CallInstruction{
        public:
            virtual Function* getTarget() const = 0;

            virtual std::list<Value*> getArgs() const = 0;
    };

    class Call: public InstructionClass<llvm::CallBase>, public CallInstruction{
        public:
            explicit Call(const llvm::CallBase &cb);

            static inline bool classof(const Call &) { return true; }
            static inline bool classof(const Call *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == CALL){ return true; }
                return false;
            }

            Call(const Call&) = delete;

            Function* getTarget() const override;

            std::list<Value*> getArgs() const override;

            const llvm::CallBase &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::CallBase& call;
    };

    //Error Instruction
    class ErrorInstruction{
        public:
            virtual std::string error() const = 0;
    };

    class UnreachableInstruction: public InstructionClass<llvm::UnreachableInst>, public ErrorInstruction{
        public:
            explicit UnreachableInstruction(const llvm::UnreachableInst &ui);

            static inline bool classof(const UnreachableInstruction &) { return true; }
            static inline bool classof(const UnreachableInstruction *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == UNREACHABLE_INSTRUCTION){ return true; }
                return false;
            }

            UnreachableInstruction(const UnreachableInstruction&) = delete;

            std::string error() const override;

            const llvm::UnreachableInst &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::UnreachableInst& unreachableInstruction;
    };

    //Return Instruction
    class ReturnInstruction{
        public:
            virtual bool returnsValue() const = 0;

            virtual Value* returnValue() const = 0;
    };

    class ReturnInst: public InstructionClass<llvm::ReturnInst>, public ReturnInstruction{
        public:
            explicit ReturnInst(const llvm::ReturnInst &retInst);

            static inline bool classof(const ReturnInst &) { return true; }
            static inline bool classof(const ReturnInst *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == RETURN_INST){ return true; }
                return false;
            }

            ReturnInst(const ReturnInst&) = delete;

            bool returnsValue() const override;

            Value* returnValue() const override;

            const llvm::ReturnInst &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::ReturnInst& returnInst;
    };

    // Assign Instruction
    class AssignInstruction{
        public:
    };

    class MemoryReadInstruction: public AssignInstruction{
        public:
            virtual InstructionVariable* getLHS() const = 0;
    };

    class SelectInst: public InstructionClass<llvm::SelectInst>, public MemoryReadInstruction{
        public:
            explicit SelectInst(const llvm::SelectInst &si);

            static inline bool classof(const SelectInst &) { return true; }
            static inline bool classof(const SelectInst *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == SELECT_INST){ return true; }
                return false;
            }

            SelectInst(const SelectInst&) = delete;

            InstructionVariable* getLHS() const override;

            Value *getCondition() const;

            Value *getTrueValue() const;

            Value *getFalseValue() const;

            const llvm::SelectInst &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::SelectInst& selectInst;
    };

    class ExtractElementInst: public InstructionClass<llvm::ExtractElementInst>, public MemoryReadInstruction{
        public:
            explicit ExtractElementInst(const llvm::ExtractElementInst &eei);

            static inline bool classof(const ExtractElementInst &) { return true; }
            static inline bool classof(const ExtractElementInst *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == EXTRACT_ELEMENT_INST){ return true; }
                return false;
            }

            ExtractElementInst(const ExtractElementInst&) = delete;

            InstructionVariable* getLHS() const override;

            Value *getVectorOperand() const;

            Value *getIndexOperand() const;

            const llvm::ExtractElementInst &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::ExtractElementInst& extractElementInst;
    };

    class ExtractValueInst: public InstructionClass<llvm::ExtractValueInst>, public MemoryReadInstruction{
    public:
        explicit ExtractValueInst(const llvm::ExtractValueInst &evi);

        static inline bool classof(const ExtractValueInst &) { return true; }
        static inline bool classof(const ExtractValueInst *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
            if (inst.getInstructionClassEnum() == EXTRACT_VALUE_INST){ return true; }
            return false;
        }

        ExtractValueInst(const ExtractValueInst&) = delete;

        InstructionVariable* getLHS() const override;

        Value *getAggregateOperand() const;

        std::list<unsigned> getIndices() const;

        const llvm::ExtractValueInst &unwrap() const override;

        void accept(InstructionClassVisitor &v) const override;

    private:
        const llvm::ExtractValueInst& extractValueInst;
    };

    class LoadInst: public InstructionClass<llvm::LoadInst>, public MemoryReadInstruction{
    public:
        explicit LoadInst(const llvm::LoadInst&);

        static inline bool classof(const LoadInst &) { return true; }
        static inline bool classof(const LoadInst *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
            if (inst.getInstructionClassEnum() == LOAD_INST){ return true; }
            return false;
        }

        LoadInst(const LoadInst&) = delete;

        InstructionVariable* getLHS() const override;

        Value *getPointerOperand() const;

        Type *getPointerOperandType() const;

        unsigned getSize() const;

        const llvm::LoadInst &unwrap() const override;

        void accept(InstructionClassVisitor &v) const override;

    private:
        const llvm::LoadInst& loadInst;
    };

    class MemoryWriteInstruction: public AssignInstruction{
        public:
            virtual MemoryAddress* getMemoryAddress() const = 0;
    };

    class InsertValueInst: public InstructionClass<llvm::InsertValueInst>, public MemoryWriteInstruction{
        public:
            explicit InsertValueInst(const llvm::InsertValueInst &ivi);

            static inline bool classof(const InsertValueInst &) { return true; }
            static inline bool classof(const InsertValueInst *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == INSERT_VALUE_INST){ return true; }
                return false;
            }

            InsertValueInst(const InsertValueInst&) = delete;

            Value *getAggregateOperand() const;

            Value *getInsertedValueOperand() const;

            std::list<unsigned> getIndices() const;

            MemoryAddress* getMemoryAddress() const override;

            const llvm::InsertValueInst &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::InsertValueInst& insertValueInst;
    };

    class InsertElementInst: public InstructionClass<llvm::InsertElementInst>, public MemoryWriteInstruction{
        public:
            explicit InsertElementInst(const llvm::InsertElementInst &iei);

            static inline bool classof(const InsertElementInst &) { return true; }
            static inline bool classof(const InsertElementInst *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == INSERT_ELEMENT_INST){ return true; }
                return false;
            }

            InsertElementInst(const InsertElementInst&) = delete;

            Value *getVector() const;

            Value *getInsertedElement() const;

            Value *getIndex() const;

            MemoryAddress* getMemoryAddress() const override;

            const llvm::InsertElementInst &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::InsertElementInst& insertElementInst;
    };

    class StoreInst: public InstructionClass<llvm::StoreInst>, public MemoryWriteInstruction{
        public:
            explicit StoreInst(const llvm::StoreInst &si);

            static inline bool classof(const StoreInst &) { return true; }
            static inline bool classof(const StoreInst *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == STORE_INST){ return true; }
                return false;
            }

            StoreInst(const StoreInst&) = delete;

            Value *getPointerOperand() const;

            Value *getValueOperand() const;

            Type *getPointerOperandType() const;

            unsigned getSize() const;

            MemoryAddress* getMemoryAddress() const override;

            const llvm::StoreInst &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::StoreInst& storeInst;
    };

    class ShuffleVectorInst: public InstructionClass<llvm::ShuffleVectorInst>, public MemoryWriteInstruction{
        public:
            explicit ShuffleVectorInst(const llvm::ShuffleVectorInst &svi);

            static inline bool classof(const ShuffleVectorInst &) { return true; }
            static inline bool classof(const ShuffleVectorInst *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == SHUFFLE_VECTOR_INST){ return true; }
                return false;
            }

            ShuffleVectorInst(const ShuffleVectorInst&) = delete;

            MemoryAddress* getMemoryAddress() const override;

            const llvm::ShuffleVectorInst &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::ShuffleVectorInst& shuffleVectorInst;
    };

    class AllocaInst: public InstructionClass<llvm::AllocaInst>, public MemoryWriteInstruction{
    public:
        explicit AllocaInst(const llvm::AllocaInst&);

        static inline bool classof(const AllocaInst &) { return true; }
        static inline bool classof(const AllocaInst *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
            if (inst.getInstructionClassEnum() == ALLOCA_INST){ return true; }
            return false;
        }

        AllocaInst(const AllocaInst&) = delete;

        Type *getAllocatedType() const;

        MemoryAddress* getMemoryAddress() const override;

        const llvm::AllocaInst &unwrap() const override;

        void accept(InstructionClassVisitor &v) const override;

    private:
        const llvm::AllocaInst &allocaInst;
    };

    class AssignInst: public AssignInstruction{
        public:
            virtual InstructionVariable* getLHS() const = 0;
    };

    class PHINode: public InstructionClass<llvm::PHINode>, public AssignInst{
        public:
            explicit PHINode(const llvm::PHINode &phin);

            static inline bool classof(const PHINode &) { return true; }
            static inline bool classof(const PHINode *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == PHI_NODE){ return true; }
                return false;
            }

            PHINode(const PHINode&) = delete;

            InstructionVariable* getLHS() const override;

            unsigned getNumIncomingValues() const;

            std::vector<Value *> getIncomingValues() const;

            std::vector<Block *> getIncomingBlocks() const;

            const llvm::PHINode &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::PHINode& phiNode;
    };

    class GetElementPtrInst: public InstructionClass<llvm::GetElementPtrInst>, public AssignInst{
        public:
            explicit GetElementPtrInst(const llvm::GetElementPtrInst &gepi);

            static inline bool classof(const GetElementPtrInst &) { return true; }
            static inline bool classof(const GetElementPtrInst *) { return true; }
            static inline bool classof(const Instruction *inst) { return classof(*inst); }
            static inline bool classof(const Instruction &inst) {
                if (inst.getInstructionClassEnum() == GET_ELEMENT_PTR_INST){ return true; }
                return false;
            }

            InstructionVariable* getLHS() const override;

            Value *getPointerOperand() const;

            Type *getPointerOperandType() const;

            const llvm::GetElementPtrInst &unwrap() const override;

            void accept(InstructionClassVisitor &v) const override;

        private:
            const llvm::GetElementPtrInst& getElementPtrInst;
    };

    class FreezeInst: public InstructionClass<llvm::FreezeInst>, public AssignInst{
    public:
        explicit FreezeInst(const llvm::FreezeInst&);

        static inline bool classof(const FreezeInst &) { return true; }
        static inline bool classof(const FreezeInst *) { return true; }
        static inline bool classof(const Instruction *inst) { return classof(*inst); }
        static inline bool classof(const Instruction &inst) {
            if (inst.getInstructionClassEnum() == FREEZE_INST){ return true; }
            return false;
        }

        FreezeInst(const FreezeInst&) = delete;

        Value* getUnaryOperand() const;

        InstructionVariable* getLHS() const override;

        const llvm::FreezeInst &unwrap() const override;

        void accept(InstructionClassVisitor &v) const override;

    private:
        const llvm::FreezeInst& freezeInst;
    };

    class InstructionClassVisitor{
    public:
        virtual void visit(const BinaryOperator &v) = 0;
        virtual void visit(const CmpInst &v) = 0;
        virtual void visit(const BranchInst &v) = 0;
        virtual void visit(const IndirectBrInst &v) = 0;
        virtual void visit(const SwitchInst &v) = 0;
        virtual void visit(const UnaryOperator &v) = 0;
        virtual void visit(const CastInst &v) = 0;
        virtual void visit(const Call &v) = 0;
        virtual void visit(const UnreachableInstruction &v) = 0;
        virtual void visit(const ReturnInst &v) = 0;
        virtual void visit(const SelectInst &v) = 0;
        virtual void visit(const ExtractElementInst &v) = 0;
        virtual void visit(const ExtractValueInst &v) = 0;
        virtual void visit(const LoadInst &v) = 0;
        virtual void visit(const InsertValueInst &v) = 0;
        virtual void visit(const InsertElementInst &v) = 0;
        virtual void visit(const StoreInst &v) = 0;
        virtual void visit(const ShuffleVectorInst &v) = 0;
        virtual void visit(const AllocaInst &v) = 0;
        virtual void visit(const PHINode &v) = 0;
        virtual void visit(const GetElementPtrInst &v) = 0;
        virtual void visit(const FreezeInst &v) = 0;
    };

}

#endif