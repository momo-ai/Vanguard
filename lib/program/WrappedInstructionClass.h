//
// Created by Jon Stephens on 8/26/22.
//

#ifndef VANGUARD_WRAPPEDINSTRUCTIONCLASS_H
#define VANGUARD_WRAPPEDINSTRUCTIONCLASS_H

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

    template<typename Derived, typename Wrap>
    class WrappedInstructionClass : public Wrapped<Derived, Wrap> {
        static_assert(std::is_base_of<llvm::Instruction, Wrap>::value, "Wrapped must inherit from LLVM instruction.");
        static_assert(std::is_base_of<vanguard::Universe::Instruction, Derived>::value, "Derived must inherit from Vanguard instruction.");
    public:

        template<typename ...Args>
        explicit WrappedInstructionClass(Args&&... args) : Wrapped<Derived, Wrap>(std::forward<Args>(args)...) {};

        std::string name() const override {
            return this->wrapped.getName().str();
        }

        Universe::Block* parent() const override {
            return this->factory.createBlk(this->wrapped.getParent());
        }

        bool willReturn() const override {
            return this->wrapped.willReturn();
        }

        Value* operand(unsigned i) const override {
            return this->factory.createVal(this->wrapped.getOperand(i));
        }

        unsigned numOperands() const override {
            return this->wrapped.getNumOperands();
        }

        const Wrap &unwrap()  const override {
            return this->wrapped;
        }

        void accept(InstructionClassVisitor &v) const override {
            auto derived = llvm::dyn_cast<Derived>(this);
            if(derived == nullptr) {
                throw std::runtime_error("Unable to cast");
            }
            else {
                v.visit(*derived);
            }
        }
    };
}


#endif //VANGUARD_WRAPPEDINSTRUCTIONCLASS_H
