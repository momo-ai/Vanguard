
//
// Created by Jon Stephens on 8/26/22.
//

#ifndef VANGUARD_UNIVERSEINSTRUCTIONCLASSES_H
#define VANGUARD_UNIVERSEINSTRUCTIONCLASSES_H

#include "Universe.h"
#include "InstructionClasses.h"
#include "llvm/IR/Instructions.h"

namespace vanguard {

    // Branch Instruction
    template<typename Base, typename Wrap>
    class Universe::BranchIns : public vanguard::BranchIns<Base> {
    public:
        template<typename ...Args>
        explicit BranchIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::BranchIns<Base>(std::forward<Args>(args)..., ins) {};

        virtual bool isConditional() const {
            return wrapped->isConditional();
        }

        virtual Value* condition() const {
            return this->factory.createVal(wrapped->getCondition());
        }

        virtual std::list<typename Base::Block*> targets() const {
            std::list<typename Base::Block*> successors = {};
            unsigned int n = wrapped->getNumSuccessors();
            for(unsigned int i = 0; i < n; i++){
                successors.push_back(dynamic_cast<typename Base::Block*>(this->factory.createBlk(wrapped->getSuccessor(i))));
            }
            return successors;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Base>
    class Universe::BranchIns<Base, llvm::SwitchInst>: public vanguard::BranchIns<Base> {
    public:
        template<typename ...Args>
        explicit BranchIns(const llvm::SwitchInst *ins, Args&&... args) : wrapped(ins), vanguard::BranchIns<Base>(std::forward<Args>(args)..., ins) {};

        virtual bool isConditional() const override {
            return true;
        }
        virtual Value* condition() const override {
            return this->factory.createVal(wrapped->getCondition());
        }
        virtual std::list<typename Base::Block*> targets() const override {
            std::list<typename Base::Block*> successors = {};
            unsigned int n = wrapped->getNumSuccessors();
            for(unsigned int i = 0; i < n; i++){
                successors.push_back(dynamic_cast<typename Base::Block*>(this->factory.createBlk(wrapped->getSuccessor(i))));
            }
            return successors;
        }

    protected:
        const llvm::SwitchInst *wrapped;
    };

    template<typename Base>
    class Universe::BranchIns<Base, llvm::IndirectBrInst>: public vanguard::BranchIns<Base> {
    public:
        template<typename ...Args>
        explicit BranchIns(const llvm::IndirectBrInst *ins, Args&&... args) : wrapped(ins), vanguard::BranchIns<Base>(std::forward<Args>(args)..., ins) {};

        virtual bool isConditional() const override {
            return false;
        }
        virtual Value* condition() const override {
            throw std::runtime_error("Indirect Branch Instruction does not have a condition.");
        }
        virtual std::list<typename Base::Block*> targets() const override {
            std::list<typename Base::Block*> successors = {};
            unsigned int n = wrapped->getNumSuccessors();
            for(unsigned int i = 0; i < n; i++){
                successors.push_back(dynamic_cast<typename Base::Block*>(this->factory.createBlk(wrapped->getSuccessor(i))));
            }
            return successors;
        }

    protected:
        const llvm::IndirectBrInst *wrapped;
    };

    //Return Instruction
    template<typename Base, typename Wrap>
    class Universe::ReturnIns : public vanguard::ReturnIns<Base> {
    public:
        template<typename ...Args>
        explicit ReturnIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::ReturnIns<Base>(std::forward<Args>(args)..., ins) {};

        bool returnsValue() const override {
            return wrapped->getReturnValue() != nullptr;
        }
        Value* value() const override {
            return this->factory.createVal(wrapped->getReturnValue());
        }

    protected:
        const Wrap *wrapped;
    };

    template<typename Base, typename Wrap>
    class Universe::ErrorIns : public vanguard::ErrorIns<Base> {
    public:
        template<typename ...Args>
        explicit ErrorIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::ErrorIns<Base>(std::forward<Args>(args)..., ins) {};


        std::string msg() const override{
            return "This instruction is unreachable.";
        }

    protected:
        const Wrap *wrapped;
    };

    /*template<typename Base, typename Wrap>
    class Universe::Expression : public vanguard::Expression<Base> {
    public:
        template<typename ...Args>
        explicit Expression(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::Expression<Base>(std::forward<Args>(args)..., ins) {};

        Value* result() const override {
            auto* insVar = this->factory.createVal(wrapped);
            return insVar;
        }

    protected:
        const Wrap *wrapped;
    };*/

    // Assign Instruction
    template<typename Base, typename Wrap>
    class Universe::AssignIns : public vanguard::AssignIns<Base> {
    public:
        template<typename ...Args>
        explicit AssignIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::AssignIns<Base>(std::forward<Args>(args)..., ins) {};


    protected:
        const Wrap *wrapped;
    };

    //BinaryOpInstruction
    template<typename Base, typename Wrap>
    class Universe::BinaryOpIns : public vanguard::BinaryOpIns<Base> {
    public:
        template<typename ...Args>
        explicit BinaryOpIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::BinaryOpIns<Base>(std::forward<Args>(args)..., ins) {};

        BinOp op() const override {
            throw std::runtime_error("Unknown op");
        }

    protected:
        const Wrap *wrapped;
    };

    template<typename Base>
    class Universe::BinaryOpIns<Base, llvm::CmpInst> : public vanguard::BinaryOpIns<Base> {
    public:
        template<typename ...Args>
        explicit BinaryOpIns(const llvm::CmpInst *ins, Args&&... args) : wrapped(ins), vanguard::BinaryOpIns<Base>(std::forward<Args>(args)..., ins) {};

        BinOp op() const override {
            unsigned opcode = wrapped->getOpcode();
            BinOp binaryOpClass;
            if (opcode == 53 || opcode == 54) binaryOpClass = IFCmpInst;
            else {
                throw std::runtime_error("The opcode "+ std::string(wrapped->getOpcodeName()) + " is not a cmp operator class in vanguard.");
            }
            return  binaryOpClass;
        }

    protected:
        const llvm::CmpInst *wrapped;
    };

    template<typename Base>
    class Universe::BinaryOpIns<Base, llvm::BinaryOperator> : public vanguard::BinaryOpIns<Base> {
    public:
        template<typename ...Args>
        explicit BinaryOpIns(const llvm::BinaryOperator *ins, Args&&... args) : wrapped(ins), vanguard::BinaryOpIns<Base>(std::forward<Args>(args)..., ins) {};

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

    protected:
        const llvm::BinaryOperator *wrapped;
    };

    //Unary Operation Instruction
    template<typename Base, typename Wrap>
    class  Universe::UnaryOpIns : public vanguard::UnaryOpIns<Base> {
    public:
        template<typename ...Args>
        explicit UnaryOpIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::UnaryOpIns<Base>(std::forward<Args>(args)..., ins) {};

        virtual UnOp op() const override {
            unsigned opcode = wrapped->getOpcode();
            UnOp unaryOpClass;
            if (opcode == 12) unaryOpClass = Neg;
            else{
                throw std::runtime_error("The opcode "+ std::string(wrapped->getOpcodeName())+ " is not a unary operator class in Vanguard.");
            }
            return unaryOpClass;
        }

        Value* operand() const override {
            return this->factory.createVal(wrapped->getOperand(0));
        }

    protected:
        const Wrap *wrapped;
    };

    template<typename Base, typename Wrap>
    class Universe::CallIns : public vanguard::CallIns<Base> {
    public:
        template<typename ...Args>
        explicit CallIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::CallIns<Base>(std::forward<Args>(args)..., ins) {};

        bool hasReturn() const override {
            return !wrapped->doesNotReturn();
        }

        std::vector<typename Base::Function*> targets() const override {
            return {dynamic_cast<typename Base::Function*>(this->factory.createFn(wrapped->getCalledFunction()))};
        }

        std::list<Value*> args() const override{
            std::list<Value*> args = {};
            for(auto itr = wrapped->arg_begin(); itr != wrapped->arg_end(); itr++){
                args.push_back(this->factory.createVal(*itr));
            }
            return args;
        }

    protected:
        const Wrap *wrapped;
    };

    template<typename Base, typename Wrap>
    class Universe::CastIns : public vanguard::CastIns<Base> {
    public:
        template<typename ...Args>
        explicit CastIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::CastIns<Base>(std::forward<Args>(args)..., ins) {};

        Type *castTo() const override {
            return this->factory.createType(wrapped->getDestTy());
        }


    protected:
        const Wrap *wrapped;
    };

    template<typename Base, typename Wrap>
    class Universe::TernaryIns : public vanguard::TernaryIns<Base> {
    public:
        template<typename ...Args>
        explicit TernaryIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::TernaryIns<Base>(std::forward<Args>(args)..., ins) {};

        Value *condition() const override {
            return this->factory.createVal(wrapped->getCondition());
        }

        Value *trueValue() const override {
            return this->factory.createVal(wrapped->getTrueValue());
        }

        Value *falseValue() const override {
            return this->factory.createVal(wrapped->getFalseValue());
        }

    protected:
        const Wrap *wrapped;
    };

    template<typename Base, typename Wrap>
    class Universe::UnknownIns : public vanguard::UnknownIns<Base> {
    public:
        template<typename ...Args>
        explicit UnknownIns(const Wrap *ins, Args&&... args) : wrapped(ins), vanguard::UnknownIns<Base>(std::forward<Args>(args)..., ins) {};


    protected:
        const Wrap *wrapped;
    };
}


#endif //VANGUARD_WRAPPEDINSTRUCTIONCLASS_H
