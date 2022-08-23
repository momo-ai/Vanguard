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
//        static_assert(std::is_base_of<llvm::Instruction, T>::value, "T must inherit from instruction.");
    public:

        explicit InstructionClass(InstructionClassEnum ice, const T &inst): Instruction(ice), instructionClassEnum(ice), instr(inst){
            instruction = llvm::dyn_cast<llvm::Instruction>(&instr);
        }

        std::string getName() override {
            return instruction->getName().str();
        }

        Block* getBlock() override{
            auto &llvmToVanguard = LLVMtoVanguard::getInstance();
            return llvmToVanguard.translateBlock(instruction->getParent());
        }

        std::string getInstructionType() override{
            return (std::string)instruction->getOpcodeName();
        }

        bool mayReadOrWriteToMemory() override{
            return instruction->mayReadOrWriteMemory();
        }

        bool willReturn() override{
            return instruction->willReturn();
        }

        Instruction* getSuccessor() override{
            auto nextInst = instruction->getNextNonDebugInstruction();
            if (nextInst == nullptr){
                return nullptr;
            }
            else{
                auto &llvmToVanguard = LLVMtoVanguard::getInstance();
                return llvmToVanguard.translateInstruction(nextInst);
            }
        }

        std::unordered_set<Instruction*> getAllSuccessors() override{
            std::unordered_set<Instruction *> allSuccessors = {};
            if (instruction->isTerminator()) {
                auto &llvmToVanguard = LLVMtoVanguard::getInstance();
                int numSuccessors = instruction->getNumSuccessors();
                for (int i = 0; i < numSuccessors; i++) {
                    allSuccessors.insert(llvmToVanguard.translateBlock(instruction->getSuccessor(i))->getInstructionsList().front());
                }
                return allSuccessors;
            }
            else{
                return allSuccessors;
            }
        }

        Value* getOperand(unsigned i) override{
            auto &llvmToVanguard = LLVMtoVanguard::getInstance();
            return llvmToVanguard.translateValue(instruction->getOperand(i));
        }

        unsigned getNumOperands() override{
            return instruction->getNumOperands();
        }

        const llvm::Instruction &unwrap() override{
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
            virtual unsigned getOpClass() = 0;

            virtual InstructionVariable* getLHS() = 0;
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

            unsigned getOpClass() override;

            InstructionVariable* getLHS() override;

            const llvm::BinaryOperator &unwrap() override;

        private:
            const llvm::BinaryOperator& binOp;
    };

    class CmpInst: public InstructionClass<llvm::CmpInst>, public BinaryOpInstruction{
        public:
            explicit CmpInst(const llvm::CmpInst &cmpinst);

            CmpInst(const CmpInst&) = delete;

            unsigned getOpClass() override;

            InstructionVariable* getLHS() override;

            const llvm::CmpInst &unwrap() override;

        private:
            const llvm::CmpInst& cmpInst;
    };

    // Branch Instruction
    class BranchInstruction{
        public:
            virtual Value* getCondition() = 0;

            virtual std::list<Block*> getSuccessors() = 0;
    };

    class BranchInst: public InstructionClass<llvm::BranchInst>, public BranchInstruction{
        public:
            explicit BranchInst( const llvm::BranchInst &brInst);

            BranchInst(const BranchInst&) = delete;

            bool isConditional();

            Value* getCondition() override;

            std::list<Block*> getSuccessors() override;

            const llvm::BranchInst &unwrap() override;

        private:
            const llvm::BranchInst& branchInst;
    };

    class IndirectBrInst: public InstructionClass<llvm::IndirectBrInst>, public BranchInstruction{
        public:
            explicit IndirectBrInst(const llvm::IndirectBrInst &ibrInst);

            IndirectBrInst(const IndirectBrInst&) = delete;

            Value * getCondition() override;

            std::list<Block*> getSuccessors() override;

            const llvm::IndirectBrInst &unwrap() override;

        private:
            const llvm::IndirectBrInst& indirectBrInst;
    };

    class SwitchInst: public InstructionClass<llvm::SwitchInst>, public BranchInstruction{
        public:
            explicit SwitchInst(const llvm::SwitchInst &swInst);

            SwitchInst(const SwitchInst&) = delete;

            Value* getCondition() override;

            std::list<Block*> getSuccessors() override;

            const llvm::SwitchInst &unwrap() override;

        private:
            const llvm::SwitchInst& switchInst;
    };

    //Unary Operation Instruction
    class  UnaryOpInstruction{
        public:
            virtual Value* getUnaryOperand() = 0;
    };

    class UnaryOperator: public InstructionClass<llvm::UnaryOperator>, public UnaryOpInstruction{
        public:
            explicit UnaryOperator(const llvm::UnaryOperator &uop);

            UnaryOperator(const UnaryOperator&) = delete;

            Value* getUnaryOperand() override;

            unsigned getOpClass();

            const llvm::UnaryOperator &unwrap() override;

        private:
            const llvm::UnaryOperator& unaryOperator;
    };

    class CastInst: public InstructionClass<llvm::CastInst>, public UnaryOpInstruction{
    public:
        explicit CastInst(const llvm::CastInst &ci);

        CastInst(const CastInst&) = delete;

        unsigned getOpClass();

        Value* getUnaryOperand() override;

        const llvm::CastInst &unwrap() override;

    private:
        const llvm::CastInst& castInst;
    };

    //Call Instruction
    class CallInstruction{
        public:
            virtual Function* getTarget() = 0;

            virtual std::list<Value*> getArgs() = 0;
    };

    class Call: public InstructionClass<llvm::CallBase>, public CallInstruction{
        public:
            explicit Call(const llvm::CallBase &cb);

            Call(const Call&) = delete;

            Function* getTarget() override;

            std::list<Value*> getArgs() override;

            const llvm::CallBase &unwrap() override;

        private:
            const llvm::CallBase& call;
    };

    //Error Instruction
    class ErrorInstruction{
        public:
            virtual std::string error() = 0;
    };

    class UnreachableInstruction: public InstructionClass<llvm::UnreachableInst>, public ErrorInstruction{
        public:
            explicit UnreachableInstruction(const llvm::UnreachableInst &ui);

            UnreachableInstruction(const UnreachableInstruction&) = delete;

            std::string error() override;

            const llvm::UnreachableInst &unwrap() override;

        private:
            const llvm::UnreachableInst& unreachableInstruction;
    };

    //Return Instruction
    class ReturnInstruction{
        public:
            virtual bool returnsValue() = 0;

            virtual Value* returnValue() = 0;
    };

    class ReturnInst: public InstructionClass<llvm::ReturnInst>, public ReturnInstruction{
        public:
            explicit ReturnInst(const llvm::ReturnInst &retInst);

            ReturnInst(const ReturnInst&) = delete;

            bool returnsValue() override;

            Value* returnValue() override;

            const llvm::ReturnInst &unwrap() override;

        private:
            const llvm::ReturnInst& returnInst;
    };

    // Assign Instruction
    class AssignInstruction{
        public:
    };

    class MemoryReadInstruction: public AssignInstruction{
        public:
            virtual InstructionVariable* getLHS() = 0;
    };

    class SelectInst: public InstructionClass<llvm::SelectInst>, public MemoryReadInstruction{
        public:
            explicit SelectInst(const llvm::SelectInst &si);

            SelectInst(const SelectInst&) = delete;

            InstructionVariable* getLHS() override;

            const llvm::SelectInst &unwrap() override;

        private:
            const llvm::SelectInst& selectInst;
    };

    class ExtractElementInst: public InstructionClass<llvm::ExtractElementInst>, public MemoryReadInstruction{
        public:
            explicit ExtractElementInst(const llvm::ExtractElementInst &eei);

            ExtractElementInst(const ExtractElementInst&) = delete;

            InstructionVariable* getLHS() override;

            const llvm::ExtractElementInst &unwrap() override;

        private:
            const llvm::ExtractElementInst& extractElementInst;
    };

    class ExtractValueInst: public InstructionClass<llvm::ExtractValueInst>, public MemoryReadInstruction{
    public:
        explicit ExtractValueInst(const llvm::ExtractValueInst &evi);

        ExtractValueInst(const ExtractValueInst&) = delete;

        InstructionVariable* getLHS() override;

        const llvm::ExtractValueInst &unwrap() override;

    private:
        const llvm::ExtractValueInst& extractValueInst;
    };

    class LoadInst: public InstructionClass<llvm::LoadInst>, public MemoryReadInstruction{
    public:
        explicit LoadInst(const llvm::LoadInst&);

        LoadInst(const LoadInst&) = delete;

        Value* getUnaryOperand();

        InstructionVariable* getLHS() override;

        const llvm::LoadInst &unwrap() override;
    private:
        const llvm::LoadInst& loadInst;
    };

    class MemoryWriteInstruction: public AssignInstruction{
        public:
            virtual MemoryAddress* getMemoryAddress() = 0;
    };

    class InsertValueInst: public InstructionClass<llvm::InsertValueInst>, public MemoryWriteInstruction{
        public:
            explicit InsertValueInst(const llvm::InsertValueInst &ivi);

            InsertValueInst(const InsertValueInst&) = delete;

            MemoryAddress* getMemoryAddress() override;

            const llvm::InsertValueInst &unwrap() override;

        private:
            const llvm::InsertValueInst& insertValueInst;
    };

    class InsertElementInst: public InstructionClass<llvm::InsertElementInst>, public MemoryWriteInstruction{
        public:
            explicit InsertElementInst(const llvm::InsertElementInst &iei);

            InsertElementInst(const InsertElementInst&) = delete;

            MemoryAddress* getMemoryAddress() override;

            const llvm::InsertElementInst &unwrap() override;

        private:
            const llvm::InsertElementInst& insertElementInst;
    };

    class StoreInst: public InstructionClass<llvm::StoreInst>, public MemoryWriteInstruction{
        public:
            explicit StoreInst(const llvm::StoreInst &si);

            StoreInst(const StoreInst&) = delete;

            MemoryAddress* getMemoryAddress() override;

            const llvm::StoreInst &unwrap() override;

        private:
            const llvm::StoreInst& storeInst;
    };

    class ShuffleVectorInst: public InstructionClass<llvm::ShuffleVectorInst>, public MemoryWriteInstruction{
        public:
            explicit ShuffleVectorInst(const llvm::ShuffleVectorInst &svi);

            ShuffleVectorInst(const ShuffleVectorInst&) = delete;

            MemoryAddress* getMemoryAddress() override;

            const llvm::ShuffleVectorInst &unwrap() override;

        private:
            const llvm::ShuffleVectorInst& shuffleVectorInst;
    };

    class AllocaInst: public InstructionClass<llvm::AllocaInst>, public MemoryWriteInstruction{
    public:
        explicit AllocaInst(const llvm::AllocaInst&);

        AllocaInst(const AllocaInst&) = delete;

        MemoryAddress* getMemoryAddress() override;

        Value* getUnaryOperand();

        const llvm::AllocaInst &unwrap() override;
    private:
        const llvm::AllocaInst &allocaInst;
    };

    class AssignInst: public AssignInstruction{
        public:
            virtual InstructionVariable* getLHS() = 0;
    };

    class PHINode: public InstructionClass<llvm::PHINode>, public AssignInst{
        public:
            explicit PHINode(const llvm::PHINode &phin);

            PHINode(const PHINode&) = delete;

            InstructionVariable* getLHS() override;

            const llvm::PHINode &unwrap() override;

        private:
            const llvm::PHINode& phiNode;
    };

    class GetElementPtrInst: public InstructionClass<llvm::GetElementPtrInst>, public AssignInst{
        public:
            explicit GetElementPtrInst(const llvm::GetElementPtrInst &gepi);

            InstructionVariable* getLHS() override;

            const llvm::GetElementPtrInst &unwrap() override;

        private:
            const llvm::GetElementPtrInst& getElementPtrInst;
    };

    class FreezeInst: public InstructionClass<llvm::FreezeInst>, public AssignInst{
    public:
        explicit FreezeInst(const llvm::FreezeInst&);

        FreezeInst(const FreezeInst&) = delete;

        Value* getUnaryOperand();

        InstructionVariable* getLHS() override;

        const llvm::FreezeInst &unwrap() override;
    private:
        const llvm::FreezeInst& freezeInst;
    };

}

#endif