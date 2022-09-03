//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKVARIABLE_H
#define LIBBLOCKCHAIN_BLKVARIABLE_H

#include <string>
#include <utility>
//#include <llvm/IR/Instruction.h>
#include <program/Type.h>
#include <program/Value.h>

namespace vanguard {
    template<typename Base>
    class BlkValue : public Base {
    public:
        template<typename ...Args>
        explicit BlkValue(Type *varType, Args&&... args) : varType(varType), Base(std::forward<Args>(args)...) {};

        Type *type() const override {
            return varType;
        }
    private:
        Type *varType;
    };

    template<typename Base>
    class BlkVariable : public BlkValue<Base> {
    public:
        template<typename ...Args>
        explicit BlkVariable(std::string name, Args&&... args) : varName(std::move(name)), BlkValue<Base>(std::forward<Args>(args)...) {};
        bool hasName() const override {
            return true;
        }

        std::string name() const override {
            return varName;
        }
    private:
        std::string varName;
    };
}



#endif //LIBBLOCKCHAIN_BLKVARIABLE_H
