#ifndef VANGUARD_PROGRAM_TYPE_H
#define VANGUARD_PROGRAM_TYPE_H

#include <list>
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"

namespace vanguard{

    class Type{
        public:
            Type();

            virtual std::string getName() = 0;
    };

    class IntegerType: public Type{
        public:
            explicit IntegerType(const llvm::IntegerType& intT);

            IntegerType(const IntegerType&) = delete;

            unsigned getWidth(); //returns width of integer in bytes

            std::string getName() override;

        private:
            const llvm::IntegerType& integer;
    };

    class ArrayType: public Type{
        public:
            explicit ArrayType(const llvm::ArrayType& array);

            ArrayType(const ArrayType&) = delete;

            Type* getBaseType();

            auto getLength();

            std::string getName() override;

        private:
            const llvm::ArrayType& array;
    };

    // class FunctionT: public Type{
    //     public:
    //         FunctionT(llvm::FunctionType& function);

    //         Type* getReturnType();

    //         unsigned getNumParams();

    //         std::list<Type*> getParamsType();

    //     private:
    //         llvm::FunctionType& function;
    // };

    class PointerType: public Type{
        public:
            explicit PointerType(const llvm::PointerType& pointer);

            PointerType(const PointerType&) = delete;
            
            bool isOpaque();

            Type* getPointeeType();

            std::string getName() override;

        private:
            const llvm::PointerType& pointer;
    };

    class StructType: public Type{
        public:
            explicit StructType(const llvm::StructType& structT);

            StructType(const StructType&) = delete;

            //struct name

            unsigned getNumFields();

            std::list<Type*> getFieldTypes();

            Type* getTypeAtIndex(unsigned n);

            std::string getName() override;

        private:
            const llvm::StructType& structT;
    };

    class VectorType: public Type{
        public:
            explicit VectorType(const llvm::VectorType& vector);

            VectorType(const VectorType&) = delete;

            Type* getBaseType();

            std::string getName() override;

            //TODO: getElementCount()
        private:
            const llvm::VectorType& vector;
    };

}

#endif