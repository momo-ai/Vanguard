#ifndef VANGUARD_PROGRAM_TYPE_H
#define VANGUARD_PROGRAM_TYPE_H

#include "Base.h"
#include "TypeClass.h"
#include <list>
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"

namespace vanguard{

    template<typename Domain>
    class Base<Domain>::Type{
    public:
        Type(typename Domain::Factory &factory, TypeSquared typeType) : factory(factory), typeType(typeType) {};
        virtual std::string name() const = 0;
        virtual void accept(TypeVisitor<Domain> &v) const = 0;
        virtual const llvm::Type *unwrap() const = 0;
    protected:
        typename Domain::Factory &factory;
        TypeSquared typeType;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::IntegerType : public vanguard::IntegerType<Domain> {
    public:
        template<typename ...Args>
        explicit IntegerType(const Wrap *ty, Args&&... args) : wrapped(ty), vanguard::IntegerType<Domain>(std::forward<Args>(args)...) {};

        unsigned int width() const override {
            return this->wrapped->getBitWidth()/8;
        }

        std::string name() const override {
            return "int" + std::to_string(width());
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::ArrayType : public vanguard::ArrayType<Domain> {
    public:
        template<typename ...Args>
        explicit ArrayType(const Wrap *ty, Args&&... args) : wrapped(ty), vanguard::ArrayType<Domain>(std::forward<Args>(args)...) {};

        virtual std::string name() const override {
            return baseType()->name() + "[]";
        }

        bool isDynamic() const override {
            return false;
        }

        Type* baseType() const override {
            return this->factory.createType(this->wrapped->getElementType());
        }

        uint64_t length() const override {
            return this->wrapped->getNumElements();
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename D>
    class Base<Domain>::ArrayType<llvm::VectorType, D> : public vanguard::ArrayType<Domain> {
    public:
        template<typename ...Args>
        explicit ArrayType(const llvm::VectorType *ty, Args&&... args) : wrapped(ty), vanguard::ArrayType<Domain>(std::forward<Args>(args)...) {};

        virtual std::string name() const override {
            return baseType()->name() + "[]";
        }

        bool isDynamic() const override {
            return false;
        }

        Type* baseType() const override {
            return this->factory.createType(this->wrapped->getElementType());
        }

        uint64_t length() const override {
            auto cnt = this->wrapped->getElementCount();
            if(cnt.isZero()) {
                return 0;
            }
            else if(cnt.isScalar()) {
                return 1;
            }
            else {
                return (uint64_t)(-1);
            }
        }

        const llvm::VectorType *unwrap() const override {
            return wrapped;
        }
    protected:
        const llvm::VectorType *wrapped;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::PointerType : public vanguard::PointerType<Domain> {
    public:
        template<typename ...Args>
        explicit PointerType(const Wrap *ty, Args&&... args) : wrapped(ty), vanguard::PointerType<Domain>(std::forward<Args>(args)...) {};

        virtual std::string name() const override {
            return this->referencedType()->name() + " *";
        }

        Type* referencedType() const override {
            return this->factory.createType(this->wrapped->getElementType());
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::StructType : public vanguard::StructType<Domain> {
    public:
        template<typename ...Args>
        explicit StructType(const Wrap *ty, Args&&... args) : wrapped(ty), vanguard::StructType<Domain>(std::forward<Args>(args)...) {};

        virtual std::string name() const override {
            return this->wrapped->getName().str();
        }

        unsigned int numFields() override {
            return this->wrapped->getStructNumElements();
        }

        std::list<Type*> fieldTypes() override {
            std::list<Type*> fieldTypesList = {};
            unsigned numFields = this->wrapped->getStructNumElements();
            for(unsigned n = 0; n < numFields; n++){
                fieldTypesList.push_back(this->factory.createType(this->wrapped->getStructElementType(n)));
            }
            return fieldTypesList;
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::VoidType : public vanguard::VoidType<Domain> {
    public:
        template<typename ...Args>
        explicit VoidType(const Wrap *ty, Args&&... args) : wrapped(ty), vanguard::VoidType<Domain>(std::forward<Args>(args)...) {};

        virtual std::string name() const override {
            return "void";
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
    };

    template<typename Domain>
    template<typename Wrap, typename D>
    class Base<Domain>::LocationType : public vanguard::LocationType<Domain> {
    public:
        template<typename ...Args>
        explicit LocationType(const Wrap *ty, Args&&... args) : wrapped(ty), vanguard::LocationType<Domain>(std::forward<Args>(args)...) {};

        virtual std::string name() const override {
            return "label";
        }

        const Wrap *unwrap() const override {
            return wrapped;
        }
    protected:
        const Wrap *wrapped;
    };
}

#endif