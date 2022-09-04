#ifndef INSTRUCTIONCLASSES_H
#define INSTRUCTIONCLASSES_H

#include "InstructionClasses.h"
#include "WrappedInstructionClass.h"

namespace vanguard{

    template<typename Domain>
    class BinaryIns: public WrappedInstructionClass<BinaryOpExpr<Domain>, Domain, llvm::BinaryOperator> {
        public:
            explicit BinaryIns(UnitFactory &factory, const llvm::BinaryOperator &bop) : WrappedInstructionClass<BinaryOpExpr<Domain>, Domain, llvm::BinaryOperator>(bop, factory) {}
            BinaryIns(const BinaryIns&) = delete;

            BinOp op() const override {
                unsigned opcode = this->wrapped.getOpcode();
                BinOp binaryOpClass;
                if (opcode == 13 || opcode == 14) binaryOpClass = Add;
                else if(opcode == 15 || opcode == 16) binaryOpClass = Sub;
                else if(opcode == 17 || opcode == 18) binaryOpClass = Mul;
                else if (opcode == 19 || opcode == 20 || opcode == 21) binaryOpClass = Div;
                else if (opcode == 22 || opcode == 23 || opcode == 24) binaryOpClass = Mod;
                else if (opcode == 25)  binaryOpClass = Shl;
                else if (opcode == 26 || opcode == 27) binaryOpClass = Shr;
                else if (opcode == 28) binaryOpClass = And;
                else if (opcode == 29) binaryOpClass = Or;
                else if (opcode == 30) binaryOpClass = Xor;
                else{
                    throw std::runtime_error("The opcode "+ std::string(this->wrapped.getOpcodeName()) + " is not a binary operator class in vanguard.");
                }
                return binaryOpClass;
            }

            Value* result() const override {
                auto* insVar = this->factory.createVal(&this->wrapped);
                return insVar;
            }
    };

    template<typename Domain>
    class CmpIns: public WrappedInstructionClass<BinaryOpExpr<Domain>, Domain, llvm::CmpInst> {
        public:
            explicit CmpIns(UnitFactory &factory, const llvm::CmpInst &cmpinst) : WrappedInstructionClass<BinaryOpExpr<Domain>, Domain, llvm::CmpInst>(cmpinst, factory) {}
            CmpIns(const CmpIns&) = delete;

            BinOp op() const override {
                unsigned opcode = this->wrapped.getOpcode();
                BinOp binaryOpClass;
                if (opcode == 53 || opcode == 54) binaryOpClass = IFCmpInst;
                else {
                    throw std::runtime_error("The opcode "+ std::string(this->wrapped.getOpcodeName()) + " is not a cmp operator class in vanguard.");
                }
                return  binaryOpClass;
            }

            Value* result() const override {
                auto* insVar = this->factory.createVal(&this->wrapped);
                return insVar;
            }
    };

    template<typename Domain>
    class BranchIns: public WrappedInstructionClass<Branch<Domain>, Domain, llvm::BranchInst> {
        public:
            explicit BranchIns(UnitFactory &factory, const llvm::BranchInst &brInst) : WrappedInstructionClass<Branch<Domain>, Domain, llvm::BranchInst>(brInst, factory) {}
            BranchIns(const BranchIns&) = delete;

            bool isConditional() const override {
                return this->wrapped.isConditional();
            }

            Value* condition() const override {
                return this->factory.createVal(this->wrapped.getCondition());
            }

            std::list<Universe::Block*> targets() const override {
                std::list<Universe::Block*> successors = {};
                unsigned int n = this->wrapped.getNumSuccessors();
                for(unsigned int i = 0; i < n; i++){
                    successors.push_back(this->factory.createBlk(this->wrapped.getSuccessor(i)));
                }
                return successors;
            }
    };

    template<typename Domain>
    class IndirectBrIns: public WrappedInstructionClass<Branch<Domain>, Domain, llvm::IndirectBrInst> {
        public:
            explicit IndirectBrIns(UnitFactory &factory, const llvm::IndirectBrInst &ibrInst) : WrappedInstructionClass<Branch<Domain>, Domain, llvm::IndirectBrInst>(ibrInst, factory) {}
            IndirectBrIns(const IndirectBrIns&) = delete;

            bool isConditional() const override {
                return false;
            }

            Value * condition() const override {
                throw std::runtime_error("Indirect Branch Instruction does not have a condition.");
            }

            std::list<Universe::Block*> targets() const override {
                std::list<Universe::Block*> successors = {};
                unsigned int n = this->wrapped.getNumSuccessors();
                for(unsigned int i = 0; i < n; i++){
                    successors.push_back(this->factory.createBlk(this->wrapped.getSuccessor(i)));
                }
                return successors;
            }
    };

    template<typename Domain>
    class SwitchIns: public WrappedInstructionClass<Branch<Domain>, Domain, llvm::SwitchInst> {
        public:
            explicit SwitchIns(UnitFactory &factory, const llvm::SwitchInst &swInst) : WrappedInstructionClass<Branch<Domain>, Domain, llvm::SwitchInst>(swInst, factory) {}
            SwitchIns(const SwitchIns&) = delete;

            bool isConditional() const override {
                return true;
            }

            Value* condition() const override {
                return this->factory.createVal(this->wrapped.getCondition());
            }

            std::list<Universe::Block*> targets() const override {
                std::list<Universe::Block*> successors = {};
                unsigned int n = this->wrapped.getNumSuccessors();
                for(unsigned int i = 0; i < n; i++){
                    successors.push_back(this->factory.createBlk(this->wrapped.getSuccessor(i)));
                }
                return successors;
            }
    };

    template<typename Domain>
    class UnaryIns: public WrappedInstructionClass<UnaryOpExpr<Domain>, Domain, llvm::UnaryOperator> {
        public:
            explicit UnaryIns(UnitFactory &factory, const llvm::UnaryOperator &uop) : WrappedInstructionClass<UnaryOpExpr<Domain>, Domain, llvm::UnaryOperator>(uop, factory) {}
            UnaryIns(const UnaryIns&) = delete;

            Value* result() const override {
                auto* insVar = this->factory.createVal(&this->wrapped);
                return insVar;
            }

            Value* operand() const override {
                return this->factory.createVal(this->wrapped.getOperand(0));
            }

            UnOp op() const override {
                unsigned opcode = this->wrapped.getOpcode();
                UnOp unaryOpClass;
                if (opcode == 12) unaryOpClass = Neg;
                else{
                    throw std::runtime_error("The opcode "+ std::string(this->wrapped.getOpcodeName())+ " is not a unary operator class in Vanguard.");
                }
                return unaryOpClass;
            }
    };

    template<typename Domain>
    class CastIns: public WrappedInstructionClass<CastExpr<Domain>, Domain, llvm::CastInst> {
    public:
        explicit CastIns(UnitFactory &factory, const llvm::CastInst &ci): WrappedInstructionClass<CastExpr<Domain>, Domain, llvm::CastInst>(ci, factory) {}
        CastIns(const CastIns&) = delete;

        Value* result() const override {
            auto* insVar = this->factory.createVal(&this->wrapped);
            return insVar;
        }

        Type *castTo() const override {
            return this->factory.createType(this->wrapped.getDestTy());
        }
    };

    template<typename Domain>
    class CallIns: public WrappedInstructionClass<CallExpr<Domain>, Domain, llvm::CallBase> {
        public:
            explicit CallIns(UnitFactory &factory, const llvm::CallBase &cb) : WrappedInstructionClass<CallExpr<Domain>, Domain, llvm::CallBase>(cb, factory) {}
            CallIns(const CallIns&) = delete;

            Value* result() const override {
                auto* insVar = this->factory.createVal(&this->wrapped);
                return insVar;
            }

            bool hasReturn() const override {
                return !this->wrapped.doesNotReturn();
            }

            Universe::Function* target() const override {
                return this->factory.createFn(this->wrapped.getCalledFunction());
            }

            std::list<Value*> args() const override {
                std::list<Value*> args = {};
                for(auto itr = this->wrapped.arg_begin(); itr != this->wrapped.arg_end(); itr++){
                    args.push_back(this->factory.createVal(*itr));
                }
                return args;
            }
    };

    template<typename Domain>
    class UnreachableIns: public WrappedInstructionClass<Error<Domain>, Domain, llvm::UnreachableInst> {
        public:
            explicit UnreachableIns(UnitFactory &factory, const llvm::UnreachableInst &ui)
                    : WrappedInstructionClass<Error<Domain>, Domain, llvm::UnreachableInst>(ui, factory) {}
            UnreachableIns(const UnreachableIns&) = delete;

            std::string msg() const override {
                return "This instruction is unreachable.";
            }
    };

    template<typename Domain>
    class ReturnIns: public WrappedInstructionClass<Return<Domain>, Domain, llvm::ReturnInst> {
        public:
            explicit ReturnIns(UnitFactory &factory, const llvm::ReturnInst &retInst) : WrappedInstructionClass<Return<Domain>, Domain, llvm::ReturnInst>(retInst, factory) {}
            ReturnIns(const ReturnIns&) = delete;

            bool returnsValue() const override {
                return this->wrapped.getReturnValue() != nullptr;
            }

            Value* value() const override {
                return this->factory.createVal(this->wrapped.getReturnValue());
            }
    };

    template<typename Domain>
    class SelectIns: public WrappedInstructionClass<TernaryExpr<Domain>, Domain, llvm::SelectInst> {
        public:
            explicit SelectIns(UnitFactory &factory, const llvm::SelectInst &si) : WrappedInstructionClass<TernaryExpr<Domain>, Domain, llvm::SelectInst>(si, factory) {}
            SelectIns(const SelectIns&) = delete;

            Value* result() const override {
                auto* insVar = this->factory.createVal(&this->wrapped);
                return insVar;
            }

            Value *condition() const override {
                return this->factory.createVal(this->wrapped.getCondition());
            }

            Value *trueValue() const override {
                return this->factory.createVal(this->wrapped.getTrueValue());
            }

            Value *falseValue() const override {
                return this->factory.createVal(this->wrapped.getFalseValue());
            }
    };

    template<typename Domain>
    class ExtractElementIns: public WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::ExtractElementInst> {
    public:
        explicit ExtractElementIns(UnitFactory &factory, const llvm::ExtractElementInst &eei)
                : WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::ExtractElementInst>(eei, factory) {}
        ExtractElementIns(const ExtractElementIns&) = delete;

        Value* result() const override {
            auto* insVar = this->factory.createVal(&this->wrapped);
            return insVar;
        }
    };

    //https://llvm.org/docs/LangRef.html#extractvalue-instruction
    template<typename Domain>
    class ExtractValueIns: public WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::ExtractValueInst> {
    public:
        explicit ExtractValueIns(UnitFactory &factory, const llvm::ExtractValueInst &evi)
                : WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::ExtractValueInst>(evi, factory) {}
        ExtractValueIns(const ExtractValueIns&) = delete;

        Value* result() const override {
            auto* insVar = this->factory.createVal(&this->wrapped);
            return insVar;
        }
    };

    template<typename Domain>
    class LoadIns: public WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::LoadInst> {
    public:
        explicit LoadIns(UnitFactory &factory, const llvm::LoadInst &li): WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::LoadInst>(li, factory) {}
        LoadIns(const LoadIns&) = delete;

        Value* result() const override {
            auto* insVar = this->factory.createVal(&this->wrapped);
            return insVar;
        }
    };

    template<typename Domain>
    class InsertValueIns: public WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::InsertValueInst> {
        public:
            explicit InsertValueIns(UnitFactory &factory, const llvm::InsertValueInst &ivi)
                    : WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::InsertValueInst>(ivi, factory) {}
            InsertValueIns(const InsertValueIns&) = delete;

            Value* result() const override {
                auto* insVar = this->factory.createVal(&this->wrapped);
                return insVar;
            }
    };

    template<typename Domain>
    class InsertElementIns: public WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::InsertElementInst> {
        public:
            explicit InsertElementIns(UnitFactory &factory, const llvm::InsertElementInst &iei)
                    : WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::InsertElementInst>(iei, factory) {}
            InsertElementIns(const InsertElementIns&) = delete;

            Value* result() const override {
                auto* insVar = this->factory.createVal(&this->wrapped);
                return insVar;
            }
    };

    template<typename Domain>
    class StoreIns: public WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::StoreInst> {
        public:
            explicit StoreIns(UnitFactory &factory, const llvm::StoreInst &si) : WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::StoreInst>(si, factory) {}
            StoreIns(const StoreIns&) = delete;

            Value* result() const override {
                auto* insVar = this->factory.createVal(&this->wrapped);
                return insVar;
            }
    };

    template<typename Domain>
    class ShuffleVectorIns: public WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::ShuffleVectorInst> {
        public:
            explicit ShuffleVectorIns(UnitFactory &factory, const llvm::ShuffleVectorInst &svi)
                    : WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::ShuffleVectorInst>(svi, factory) {}
            ShuffleVectorIns(const ShuffleVectorIns&) = delete;

            Value* result() const override {
                auto* insVar = this->factory.createVal(&this->wrapped);
                return insVar;
            }
    };

    template<typename Domain>
    class AllocaIns: public WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::AllocaInst> {
    public:
        explicit AllocaIns(UnitFactory &factory, const llvm::AllocaInst &ai): WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::AllocaInst>(ai, factory) {}
        AllocaIns(const AllocaIns&) = delete;

        Value* result() const override {
            auto* insVar = this->factory.createVal(&this->wrapped);
            return insVar;
        }
    };

    template<typename Domain>
    class PHIIns: public WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::PHINode> {
        public:
            explicit PHIIns(UnitFactory &factory, const llvm::PHINode &phin) : WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::PHINode>(phin, factory) {}
            PHIIns(const PHIIns&) = delete;

            Value* result() const override {
                auto* insVar = this->factory.createVal(&this->wrapped);
                return insVar;
            }
    };

    template<typename Domain>
    class GetElementPtrIns: public WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::GetElementPtrInst> {
        public:
            explicit GetElementPtrIns(UnitFactory &factory, const llvm::GetElementPtrInst &gepi)
                    : WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::GetElementPtrInst>(gepi, factory) {}

            Value* result() const override {
                auto* insVar = this->factory.createVal(&this->wrapped);
                return insVar;
            }
    };

    template<typename Domain>
    class FreezeIns: public WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::FreezeInst> {
    public:
        explicit FreezeIns(UnitFactory &factory, const llvm::FreezeInst &fi): WrappedInstructionClass<UnknownExpr<Domain>, Domain, llvm::FreezeInst>(fi, factory) {}
        FreezeIns(const FreezeIns&) = delete;

        Value* result() const override {
            auto* insVar = this->factory.createVal(&this->wrapped);
            return insVar;
        }
    };

}

#endif