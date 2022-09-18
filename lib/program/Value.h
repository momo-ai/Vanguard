#ifndef VANGUARD_PROGRAM_VALUE_H
#define VANGUARD_PROGRAM_VALUE_H

#include "Base.h"
#include <string>
#include "llvm/IR/Value.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Instruction.h"
#include "ValueClasses.h"

namespace vanguard{

    template<typename Domain>
    class Base<Domain>::Value {
    public:
        explicit Value(typename Domain::Factory &factory, ValueClassEnum vc) : factory(factory), valClass(vc) {};

        static inline bool classof(const Value &) { return true; }
        static inline bool classof(const Value *) { return true; }

        virtual typename Domain::Type* type() const {
            return this->factory.createType(unwrap()->getType());
        }

        ValueClassEnum valueClass() const {
            return valClass;
        }

        virtual void accept(ValueClassVisitor<Domain> &v) const = 0;
        virtual const llvm::Value *unwrap() const = 0;

    protected:
        ValueClassEnum valClass;
        typename Domain::Factory &factory;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::Variable : public vanguard::Variable<Domain> {
    public:
        template<typename ...Args>
        explicit Variable(const Wrap *val, Args&&... args) : wrapped(val), vanguard::Variable<Domain>(std::forward<Args>(args)...) {};

        bool hasName() const override {
            return this->wrapped->hasName();
        }

        std::string name() const override {
            return this->wrapped->getName().str();
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::Constant : public vanguard::Constant<Domain> {
    public:
        template<typename ...Args>
        explicit Constant(const Wrap *val, Args&&... args) : wrapped(val), vanguard::Constant<Domain>(std::forward<Args>(args)...) {};

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::Literal : public vanguard::Literal<Domain> {
    public:
        template<typename ...Args>
        explicit Literal(const Wrap *val, Args&&... args) : wrapped(val), vanguard::Literal<Domain>(std::forward<Args>(args)...) {};

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::Pointer : public vanguard::Pointer<Domain> {
    public:
        template<typename ...Args>
        explicit Pointer(const Wrap *val, const llvm::Value *offset, Args&&... args) : wrapped(val), ptrOffset(offset), vanguard::Pointer<Domain>(std::forward<Args>(args)...) {};

        Value *base() const override {
            return this->factory.createVal(&this->wrapped);
        }

        Value *offset() const override {
            return this->factory.createVal(ptrOffset);
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
        const llvm::Value *ptrOffset;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::MemoryRegion : public vanguard::MemoryRegion<Domain> {
    public:
        template<typename ...Args>
        explicit MemoryRegion(const Wrap *val, Args&&... args) : wrapped(val), vanguard::MemoryRegion<Domain>(std::forward<Args>(args)...) {};

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::Location : public vanguard::Location<Domain> {
    public:
        template<typename ...Args>
        explicit Location(const Wrap *val, Args&&... args) : wrapped(val), vanguard::Location<Domain>(std::forward<Args>(args)...) {};

        typename Domain::Block &loc() const override {
            return *this->factory.createBlk(this->wrapped);
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
    };
}

#endif