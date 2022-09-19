//
// Created by Jon Stephens on 9/18/22.
//

#ifndef VANGUARD_LIBBLOCKCHAIN_VALUE_H
#define VANGUARD_LIBBLOCKCHAIN_VALUE_H

#include <string>
#include "Blockchain.h"

namespace vanguard {
    template<class Base, class Domain>
    class Blockchain<Base, Domain>::Value : public Base::Value {
    public:
        template<typename ...Args>
        explicit Value(Args&&... args) : Base::Value(std::forward<Args>(args)...) {};

    private:
    };

    template<class Base, class Domain>
    template<typename Wrap, typename D>
    class Blockchain<Base, Domain>::BlkVariable : public Base::template Variable<Wrap, D> {
    public:
        template<typename ...Args>
        explicit BlkVariable(std::string name, typename Domain::Type *varType, Args&&... args) : varType(varType), varName(std::move(name)), Base::template Variable<Wrap, D>(std::forward<Args>(args)...) {};

        bool hasName() const override {
            return true;
        }

        std::string name() const override {
            return varName;
        }

        typename Domain::Type* type() const override {
            return varType;
        }
    private:
        typename Domain::Type *varType;
        std::string varName;
    };
}
#endif //VANGUARD_VALUE_H
