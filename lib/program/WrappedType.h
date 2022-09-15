//
// Created by Jon Stephens on 9/2/22.
//

#ifndef VANGUARD_WRAPPEDTYPE_H
#define VANGUARD_WRAPPEDTYPE_H

#include "Type.h"
#include "Wrapped.h"

namespace vanguard {
    template<typename Base, typename Wrap>
    class WrappedType : public Wrapped<Base, Wrap> {
    public:
        template<typename ...Args>
        explicit WrappedType(Args&&... args) : Wrapped<Base, Wrap>(std::forward<Args>(args)...) {};

    };

    template<typename Base>
    class WrappedIntegerType : public WrappedType<Base, llvm::IntegerType> {
    public:
        template<typename ...Args>
        explicit WrappedIntegerType(Args&&... args) : WrappedType<Base, llvm::IntegerType>(std::forward<Args>(args)...) {};

        unsigned int width() const override {
            return this->wrapped.getBitWidth()/8;
        }

        std::string name() const override {
            return "int" + std::to_string(width());
        }
    };

    template<typename Base, typename Wrap>
    class WrappedArrayType : public WrappedType<Base, Wrap> {
    public:
        template<typename ...Args>
        explicit WrappedArrayType(Args&&... args) : WrappedType<Base, Wrap>(std::forward<Args>(args)...) {};

        virtual std::string name() const override {
            return baseType()->name() + "[]";
        }

        bool isDynamic() const override {
            return false;
        }

        Type* baseType() const override {
            return this->factory.createType(this->wrapped.getElementType());
        }

        uint64_t length() const override {
            return this->wrapped.getNumElements();
        }
    };

    template<typename Base>
    class WrappedVectorType : public WrappedType<Base, llvm::VectorType> {
    public:
        template<typename ...Args>
        explicit WrappedVectorType(Args&&... args) : WrappedType<Base, llvm::VectorType>(std::forward<Args>(args)...) {};

        virtual std::string name() const override {
            return baseType()->name() + "[]";
        }

        bool isDynamic() const override {
            return false;
        }

        Type* baseType() const override {
            return this->factory.createType(this->wrapped.getElementType());
        }

        uint64_t length() const override {
            auto cnt = this->wrapped.getElementCount();
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
    };

    template<typename Base, typename Wrap>
    class WrappedPointerType : public WrappedType<Base, Wrap> {
    public:
        template<typename ...Args>
        explicit WrappedPointerType(Args&&... args) : WrappedType<Base, Wrap>(std::forward<Args>(args)...) {};

        virtual std::string name() const override {
            return this->referencedType()->name() + " *";
        }

        Type* referencedType() const override {
            return this->factory.createType(this->wrapped.getElementType());
        }
    };

    template<typename Base, typename Wrap>
    class WrappedStructType : public WrappedType<Base, Wrap> {
    public:
        template<typename ...Args>
        explicit WrappedStructType(Args&&... args) : WrappedType<Base, Wrap>(std::forward<Args>(args)...) {};

        virtual std::string name() const override {
            return this->wrapped.getName().str();
        }

        unsigned int numFields() override {
            return this->wrapped.getStructNumElements();
        }

        std::list<Type*> fieldTypes() override {
            std::list<Type*> fieldTypesList = {};
            unsigned numFields = this->wrapped.getStructNumElements();
            for(unsigned n = 0; n < numFields; n++){
                fieldTypesList.push_back(this->factory.createType(this->wrapped.getStructElementType(n)));
            }
            return fieldTypesList;
        }
    };

    template<typename Base, typename Wrap>
    class WrappedVoidType : public WrappedType<Base, Wrap> {
    public:
        template<typename ...Args>
        explicit WrappedVoidType(Args&&... args) : WrappedType<Base, Wrap>(std::forward<Args>(args)...) {};

        virtual std::string name() const override {
            return "void";
        }
    };

    template<typename Base, typename Wrap>
    class WrappedLocationType : public WrappedType<Base, Wrap> {
    public:
        template<typename ...Args>
        explicit WrappedLocationType(Args&&... args) : WrappedType<Base, Wrap>(std::forward<Args>(args)...) {};

        virtual std::string name() const override {
            return "label";
        }
    };
}

#endif //VANGUARD_WRAPPEDTYPE_H
