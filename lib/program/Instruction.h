//
// Created by Jon Stephens on 8/26/22.
//

#ifndef VANGUARD_INSTRUCTION_H
#define VANGUARD_INSTRUCTION_H

#include "Base.h"
#include "InstructionClasses.h"
#include "llvm/IR/Instructions.h"

namespace vanguard {

    template<typename Domain>
    class Base<Domain>::Instruction {
    public:
        explicit Instruction(typename Domain::Factory &factory) : factory(factory) {};
        static inline bool classof(const Instruction &) { return true; }
        static inline bool classof(const Instruction *) { return true; }

        virtual InstructionClassEnum instructionClass() const = 0;
        virtual void accept(InstructionClassVisitor<Domain> &v) const = 0;
        virtual std::string name() const {
            return unwrap()->getName().str();
        }
        virtual bool willReturn() const {
            return unwrap()->willReturn();
        }
        virtual typename Domain::Value* operandAt(unsigned i) const {
            return factory.createVal(unwrap()->getOperand(i));
        }
        virtual unsigned numOperands() const {
            return unwrap()->getNumOperands();
        }
        virtual const llvm::Instruction *unwrap() const = 0;
        //virtual std::vector<Value *> reads();
        //virtual std::vector<Value *> writes();
        virtual typename Domain::Block* block() const {
            return factory.createBlk(unwrap()->getParent());
        }
    protected:
        typename Domain::Factory &factory;
    };

    // Branch Instruction
    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::BranchIns : public vanguard::BranchIns<Domain> {
    public:
        template<typename ...Args>
        explicit BranchIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::BranchIns<Domain>(std::forward<Args>(args)...) {};

        bool isConditional() const override {
            return wrapped->isConditional();
        }

        typename Domain::Value* condition() const override {
            return this->factory.createVal(wrapped->getCondition());
        }

        std::list<typename Domain::Block*> targets() const override {
            std::list<typename Domain::Block*> successors = {};
            unsigned int n = wrapped->getNumSuccessors();
            for(unsigned int i = 0; i < n; i++){
                successors.push_back(dynamic_cast<typename Domain::Block*>(this->factory.createBlk(wrapped->getSuccessor(i))));
            }
            return successors;
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename D>
    class Base<Domain>::BranchIns<llvm::SwitchInst, D>: public vanguard::BranchIns<Domain> {
    public:
        template<typename ...Args>
        explicit BranchIns(const llvm::SwitchInst *ins, Args&&... args) : wrapped(ins), vanguard::BranchIns<Domain>(std::forward<Args>(args)...) {};

        bool isConditional() const override {
            return true;
        }
        typename Domain::Value* condition() const override {
            return this->factory.createVal(wrapped->getCondition());
        }
        std::list<typename Domain::Block*> targets() const override {
            std::list<typename Domain::Block*> successors = {};
            unsigned int n = wrapped->getNumSuccessors();
            for(unsigned int i = 0; i < n; i++){
                successors.push_back(dynamic_cast<typename Domain::Block*>(this->factory.createBlk(wrapped->getSuccessor(i))));
            }
            return successors;
        }

        const llvm::SwitchInst *unwrap() const override {
            return wrapped;
        }
    protected:
        const llvm::SwitchInst *wrapped;
    };

    template<typename Domain>
    template<typename D>
    class Base<Domain>::BranchIns<llvm::IndirectBrInst, D>: public vanguard::BranchIns<Domain> {
    public:
        template<typename ...Args>
        explicit BranchIns(const llvm::IndirectBrInst *ins, Args&&... args) : wrapped(ins), vanguard::BranchIns<Domain>(std::forward<Args>(args)...) {};

        bool isConditional() const override {
            return false;
        }
        typename Domain::Value* condition() const override {
            throw std::runtime_error("Indirect Branch Instruction does not have a condition.");
        }
        std::list<typename Domain::Block*> targets() const override {
            std::list<typename Domain::Block*> successors = {};
            unsigned int n = wrapped->getNumSuccessors();
            for(unsigned int i = 0; i < n; i++){
                successors.push_back(dynamic_cast<typename Domain::Block*>(this->factory.createBlk(wrapped->getSuccessor(i))));
            }
            return successors;
        }

        const llvm::IndirectBrInst *unwrap() const override {
            return wrapped;
        }
    protected:
        const llvm::IndirectBrInst *wrapped;
    };

    //Return Instruction
    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::ReturnIns : public vanguard::ReturnIns<Domain> {
    public:
        template<typename ...Args>
        explicit ReturnIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::ReturnIns<Domain>(std::forward<Args>(args)...) {};

        bool returnsValue() const override {
            return wrapped->getReturnValue() != nullptr;
        }
        typename Domain::Value* value() const override {
            return this->factory.createVal(wrapped->getReturnValue());
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::ErrorIns : public vanguard::ErrorIns<Domain> {
    public:
        template<typename ...Args>
        explicit ErrorIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::ErrorIns<Domain>(std::forward<Args>(args)...) {};


        std::string msg() const override{
            return "This instruction is unreachable.";
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
    };

    // Assign Instruction
    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::AssignIns : public vanguard::AssignIns<Domain> {
    public:
        template<typename ...Args>
        explicit AssignIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::AssignIns<Domain>(std::forward<Args>(args)...) {};

        const Wrap *unwrap() const override {
            return wrapped;
        }

        typename Domain::Value* result() const override {
            auto* insVar = this->factory.createVal(wrapped);
            return insVar;
        }
    protected:
        const Wrap *wrapped;
    };

    //BinaryOpInstruction
    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::BinaryOpIns : public vanguard::BinaryOpIns<Domain> {
    public:
        template<typename ...Args>
        explicit BinaryOpIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::BinaryOpIns<Domain>(std::forward<Args>(args)...) {};

        BinOp op() const override {
            throw std::runtime_error("Unknown op");
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }

        typename Domain::Value* result() const override {
            auto* insVar = this->factory.createVal(wrapped);
            return insVar;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename D>
    class Base<Domain>::BinaryOpIns<llvm::CmpInst, D> : public vanguard::BinaryOpIns<Domain> {
    public:
        template<typename ...Args>
        explicit BinaryOpIns(const llvm::CmpInst *ins, Args&&... args) : wrapped(ins), vanguard::BinaryOpIns<Domain>(std::forward<Args>(args)...) {};

        BinOp op() const override {
            unsigned opcode = wrapped->getOpcode();
            BinOp binaryOpClass;
            if (opcode == 53 || opcode == 54) binaryOpClass = IFCmpInst;
            else {
                throw std::runtime_error("The opcode "+ std::string(wrapped->getOpcodeName()) + " is not a cmp operator class in vanguard.");
            }
            return  binaryOpClass;
        }

        const llvm::CmpInst *unwrap() const override {
            return wrapped;
        }

        typename Domain::Value* result() const override {
            auto* insVar = this->factory.createVal(wrapped);
            return insVar;
        }
    protected:
        const llvm::CmpInst *wrapped;
    };

    template<typename Domain>
    template<typename D>
    class Base<Domain>::BinaryOpIns<llvm::BinaryOperator, D> : public vanguard::BinaryOpIns<Domain> {
    public:
        template<typename ...Args>
        explicit BinaryOpIns(const llvm::BinaryOperator *ins, Args&&... args) : wrapped(ins), vanguard::BinaryOpIns<Domain>(std::forward<Args>(args)...) {};

        BinOp op() const override {
            unsigned opcode = wrapped->getOpcode();
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
                throw std::runtime_error("The opcode "+ std::string(wrapped->getOpcodeName()) + " is not a binary operator class in vanguard.");
            }
            return binaryOpClass;
        }

        const llvm::BinaryOperator *unwrap() const override {
            return wrapped;
        }

        typename Domain::Value* result() const override {
            auto* insVar = this->factory.createVal(wrapped);
            return insVar;
        }
    protected:
        const llvm::BinaryOperator *wrapped;
    };

    //Unary Operation Instruction
    template<typename Domain>
    template<typename Wrap, typename D>
    class  Base<Domain>::UnaryOpIns : public vanguard::UnaryOpIns<Domain> {
    public:
        template<typename ...Args>
        explicit UnaryOpIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::UnaryOpIns<Domain>(std::forward<Args>(args)...) {};

        UnOp op() const override {
            unsigned opcode = wrapped->getOpcode();
            UnOp unaryOpClass;
            if (opcode == 12) unaryOpClass = Neg;
            else{
                throw std::runtime_error("The opcode "+ std::string(wrapped->getOpcodeName())+ " is not a unary operator class in Vanguard.");
            }
            return unaryOpClass;
        }

        typename Domain::Value* operand() const override {
            return this->factory.createVal(wrapped->getOperand(0));
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }

        typename Domain::Value* result() const override {
            auto* insVar = this->factory.createVal(wrapped);
            return insVar;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::CallIns : public vanguard::CallIns<Domain> {
    public:
        template<typename ...Args>
        explicit CallIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::CallIns<Domain>(std::forward<Args>(args)...) {};

        bool hasReturn() const override {
            return !wrapped->doesNotReturn();
        }

        std::vector<typename Domain::Function*> targets() const override {
            return {dynamic_cast<typename Domain::Function*>(this->factory.createFn(wrapped->getCalledFunction()))};
        }

        std::list<typename Domain::Value*> args() const override{
            std::list<typename Domain::Value*> args = {};
            for(auto itr = wrapped->arg_begin(); itr != wrapped->arg_end(); itr++){
                args.push_back(this->factory.createVal(*itr));
            }
            return args;
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }

        typename Domain::Value* result() const override {
            auto* insVar = this->factory.createVal(wrapped);
            return insVar;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::CastIns : public vanguard::CastIns<Domain> {
    public:
        template<typename ...Args>
        explicit CastIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::CastIns<Domain>(std::forward<Args>(args)...) {};

        typename Domain::Type *castTo() const override {
            return this->factory.createType(wrapped->getDestTy());
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }

        typename Domain::Value* result() const override {
            auto* insVar = this->factory.createVal(wrapped);
            return insVar;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::TernaryIns : public vanguard::TernaryIns<Domain> {
    public:
        template<typename ...Args>
        explicit TernaryIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::TernaryIns<Domain>(std::forward<Args>(args)...) {};

        typename Domain::Value *condition() const override {
            return this->factory.createVal(wrapped->getCondition());
        }

        typename Domain::Value *trueValue() const override {
            return this->factory.createVal(wrapped->getTrueValue());
        }

        typename Domain::Value *falseValue() const override {
            return this->factory.createVal(wrapped->getFalseValue());
        }
        const Wrap *unwrap() const override {
            return wrapped;
        }

        typename Domain::Value* result() const override {
            auto* insVar = this->factory.createVal(wrapped);
            return insVar;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::UnknownIns : public vanguard::UnknownIns<Domain> {
    public:
        template<typename ...Args>
        explicit UnknownIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::UnknownIns<Domain>(std::forward<Args>(args)...) {};

        const Wrap *unwrap() const override {
            return wrapped;
        }

        typename Domain::Value* result() const override {
            auto* insVar = this->factory.createVal(wrapped);
            return insVar;
        }
    protected:
        const Wrap *wrapped;
    };
}


#endif //VANGUARD_INSTRUCTION_H
