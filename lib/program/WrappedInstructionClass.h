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

namespace vanguard {

    template<typename Derived, typename Wrapped> class WrappedInstructionClass : public Derived {
        static_assert(std::is_base_of<llvm::Instruction, Wrapped>::value, "Wrapped must inherit from LLVM instruction.");
        static_assert(std::is_base_of<vanguard::Universe::Instruction, Derived>::value, "Derived must inherit from Vanguard instruction.");
    public:

        explicit WrappedInstructionClass(UnitFactory &factory, const Wrapped &inst): ins(inst), factory(factory) {}

        std::string name() const override {
            return ins.getName().str();
        }

        Universe::Block* parent() const override {
            return factory.createBlk(ins.getParent());
        }

        bool mayReadOrWriteToMemory() const override {
            return ins.mayReadOrWriteMemory();
        }

        bool willReturn() const override {
            return ins.willReturn();
        }

        Universe::Instruction* getSuccessor() const override {
            if (ins.isTerminator()){
                return nullptr;
            }
            auto nextInst = ins.getNextNonDebugInstruction();
            if (nextInst == nullptr){
                return nullptr;
            }
            else{
                return factory.createIns(nextInst);
            }
        }

        std::list<Universe::Instruction*> getAllSuccessors() const override  {
            std::list<Universe::Instruction *> allSuccessors = {};
            if (ins.isTerminator()) {
                int numSuccessors = ins.getNumSuccessors();
                for (int i = 0; i < numSuccessors; i++) {
                    allSuccessors.push_back(factory.createBlk(ins.getSuccessor(i))->instructions().front());
                }
                return allSuccessors;
            }
            else{
                return allSuccessors;
            }
        }

        Value* operand(unsigned i) const override {
            return factory.createVal(ins.getOperand(i));
        }

        unsigned numOperands() const override {
            return ins.getNumOperands();
        }

        const Wrapped &unwrap()  const override {
            return ins;
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

    protected:
        const Wrapped &ins;
        UnitFactory &factory;
    };
}


#endif //VANGUARD_WRAPPEDINSTRUCTIONCLASS_H
