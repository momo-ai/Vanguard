//
// Created by Jon Stephens on 9/2/22.
//

#ifndef VANGUARD_WRAPPEDVALUE_H
#define VANGUARD_WRAPPEDVALUE_H

#include <utility>
#include "Value.h"

namespace vanguard {
    template<typename Base, typename Wrapped>
    class WrappedValue : public Base {
    public:
        template<typename ...Args>
        explicit WrappedValue(const Wrapped &w, Args&&... args) : wrapped(w), Base(std::forward<Args>(args)...) {};

        Type* type() const override {
            return this->factory.createType(wrapped.getType());
        }

        Wrapped &unwrap() { return wrapped; }
    protected:
        const Wrapped &wrapped;
    };

    template<typename Base, typename Wrapped>
    class WrappedVariable : public WrappedValue<Base, Wrapped> {
    public:
        template<typename ...Args>
        explicit WrappedVariable(Args&&... args) : WrappedValue<Base, Wrapped>(std::forward<Args>(args)...) {};

        /*Type* type() const override {
            return WrappedValue<Base, Wrapped>::type();
        }*/

        bool hasName() const override {
            return this->wrapped.hasName();
        }

        std::string name() const override {
            return this->wrapped.getName().str();
        }
    };

    template<typename Base, typename Wrapped>
    class WrappedConstant : public WrappedValue<Base, Wrapped> {
    public:
        template<typename ...Args>
        explicit WrappedConstant(Args&&... args) : WrappedValue<Base, Wrapped>(std::forward<Args>(args)...) {};
    };

    template<typename Base, typename Wrapped>
    class WrappedLiteral : public WrappedValue<Base, Wrapped> {
    public:
        template<typename ...Args>
        explicit WrappedLiteral(Args&&... args) : WrappedValue<Base, Wrapped>(std::forward<Args>(args)...) {};
    };

    template<typename Base, typename Wrapped>
    class WrappedPointer : public WrappedValue<Base, Wrapped> {
    public:
        template<typename ...Args>
        explicit WrappedPointer(const Wrapped &base, const llvm::Value *offset, Args&&... args) : WrappedValue<Base, Wrapped>(base, std::forward<Args>(args)...) {};

        Value *base() const override {
            return this->factory.createVal(&this->wrapped);
        }

        Value *offset() const override {
            return this->factory.createVal(ptrOffset);
        }

        /*Type *refType() const override {

        }*/
    private:
        const llvm::Value *ptrOffset;
    };

    template<typename Base, typename Wrapped>
    class WrappedMemoryRegion : public WrappedValue<Base, Wrapped> {
    public:
        template<typename ...Args>
        explicit WrappedMemoryRegion(Args&&... args) : WrappedValue<Base, Wrapped>(std::forward<Args>(args)...) {};
    };

    template<typename Base, typename Wrapped>
    class WrappedLocation : public WrappedValue<Base, Wrapped> {
    public:
        template<typename ...Args>
        explicit WrappedLocation(Args&&... args) : WrappedValue<Base, Wrapped>(std::forward<Args>(args)...) {};

        virtual Universe::Block &loc() const  {
            return *this->factory.createBlk(&(this->wrapped));
        }
    };
}



#endif //VANGUARD_WRAPPEDVALUE_H
