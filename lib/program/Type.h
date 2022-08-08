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

    class IntegerT: public Type{
        public:
            IntegerT(llvm::IntegerType& intT);

            unsigned getWidth(); //returns width of integer in bytes

            std::string getName() override;

        private:
            llvm::IntegerType& integer;
    };

    class ArrayT: public Type{
        public:
            ArrayT(llvm::ArrayType& array);

            Type* getBaseType();

            auto getLength();

            std::string getName() override;

        private:
            llvm::ArrayType& array;
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

    class PointerT: public Type{
        public:
            PointerT(llvm::PointerType& pointer);
            
            bool isOpaque();

            Type* getPointeeType();

            std::string getName() override;

        private:
            llvm::PointerType& pointer;
    };

    class StructT: public Type{
        public:
            StructT(llvm::StructType& structT);

            //struct name

            unsigned getNumFields();

            std::list<Type*> getFieldTypes();

            Type* getTypeAtIndex(unsigned n);

            std::string getName() override;

        private:
            llvm::StructType& structT;
    };

    class VectorT: public Type{
        public:
            VectorT(llvm::VectorType& vector);

            Type* getBaseType();

            std::string getName() override;

            //TODO: getElementCount()
        private:
            llvm::VectorType& vector;
    };

}

#endif