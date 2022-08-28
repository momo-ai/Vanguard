#ifndef VANGUARD_PROGRAM_TYPE_H
#define VANGUARD_PROGRAM_TYPE_H

#include <list>
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"

namespace vanguard{

    class Type{
        public:
            Type();

            virtual std::string name() const = 0;
    };

    class IntegerType: public Type{
        public:
            explicit IntegerType(const llvm::IntegerType&);

            IntegerType(const IntegerType&) = delete;

            unsigned width(); //returns width of integer in bytes

            std::string name() const override;

            const llvm::IntegerType &unwrap();

        private:
            const llvm::IntegerType& integer;
    };

    class ArrayType: public Type{
        public:
            explicit ArrayType(const llvm::ArrayType&);

            ArrayType(const ArrayType&) = delete;

            Type* baseType() const;

            uint64_t length() const;

            std::string name() const override;

            const llvm::ArrayType &unwrap();

        private:
            const llvm::ArrayType& array;
    };

//     class FunctionT: public Type{
//         public:
//             explicit FunctionT(const llvm::FunctionType& function);
//
//             std::string name() override;
//
//             Type* returnType();
//
//             unsigned getNumParams();
//
//             std::list<Type*> getParamsType();
//
//         private:
//             const llvm::FunctionType& function;
//     };

    class PointerType: public Type{
        public:
            explicit PointerType(const llvm::PointerType& pointer);

            PointerType(const PointerType&) = delete;
            
            bool isOpaque();

            Type* referencedType() const;

            std::string name() const override;

            const llvm::PointerType &unwrap();

        private:
            const llvm::PointerType& pointer;
    };

    class StructType: public Type{
        public:
            explicit StructType(const llvm::StructType& structT);

            StructType(const StructType&) = delete;

            //struct name

            unsigned numFields();

            std::list<Type*> fieldTypes();

            Type* getTypeAtIndex(unsigned n);

            std::string name() const override;

            const llvm::StructType &unwrap();

        private:
            const llvm::StructType& structT;
    };

    class VectorType: public Type{
        public:
            explicit VectorType(const llvm::VectorType& vector);

            VectorType(const VectorType&) = delete;

            Type* baseType() const;

            std::string name() const override;

            const llvm::VectorType &unwrap();

            //TODO: getElementCount()
        private:
            const llvm::VectorType& vector;
    };

    class VoidType: public Type{
        public:
            explicit VoidType(const llvm::Type&);

            VoidType(const VoidType&) = delete;

            std::string name() const override;

            const llvm::Type &unwrap();

        private:
            const llvm::Type& voidType;
    };

    class LabelType: public Type{
    public:
        explicit  LabelType(const llvm::Type&);

        LabelType(const LabelType&) = delete;

        std::string name() const override;

        const llvm::Type &unwrap();

    private:
        const llvm::Type& labelType;
    };
}

#endif