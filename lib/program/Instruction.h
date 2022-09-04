//
// Created by Jon Stephens on 8/26/22.
//

#ifndef VANGUARD_INSTRUCTION_CPP
#define VANGUARD_INSTRUCTION_CPP

#include "Universe.h"
#include "Value.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include "LLVMFactory.h"
#include <string>
#include <list>
#include "InstructionClassVisitor.h"
#include "Block.h"
#include "Wrapped.h"

namespace vanguard {

    class Universe::Instruction {
    public:
        explicit Instruction(UnitFactory &factory, const llvm::Instruction *ins) : ins(ins), factory(factory) {};
        static inline bool classof(const Instruction &) { return true; }
        static inline bool classof(const Instruction *) { return true; }

        virtual InstructionClassEnum instructionClass() const = 0;
        virtual std::string name() const {
            return ins->getName().str();
        }

        virtual Block* parent() const {
            return factory.createBlk(ins->getParent());
        }

        virtual bool willReturn() const {
            return ins->willReturn();
        }

        virtual Value* operandAt(unsigned i) const {
            return factory.createVal(ins->getOperand(i));
        }

        virtual unsigned numOperands() const {
            return ins->getNumOperands();
        }

        virtual const llvm::Instruction &unwrap() const {
            return *ins;
        }
        //virtual std::vector<Value *> reads();
        //virtual std::vector<Value *> writes();
    protected:
        const llvm::Instruction* ins;
        UnitFactory &factory;
    };

    /*void Universe::Instruction::accept(InstructionClassVisitor<Domain> &v) const override {
        auto derived = llvm::dyn_cast<Derived>(this);
        if(derived == nullptr) {
            throw std::runtime_error("Unable to cast");
        }
        else {
            v.visit(*derived);
        }
    }*/
}


#endif //VANGUARD_INSTRUCTION_CPP
