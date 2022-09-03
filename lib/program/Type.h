#ifndef VANGUARD_PROGRAM_TYPE_H
#define VANGUARD_PROGRAM_TYPE_H

#include <list>
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"

namespace vanguard{
    class UnitFactory;
    enum TypeSquared {
        INT_TYPE,
        ARRAY_TYPE,
        MAP_TYPE,
        OBJECT_TYPE,
        POINTER_TYPE,
        STRUCT_TYPE,
        VOID_TYPE,
        LOCATION_TYPE,
        UNKNOWN_TYPE
    };

    class TypeVisitor;

    class Type{
    public:
        Type(UnitFactory &factory, TypeSquared typeType);
        virtual std::string name() const = 0;
        virtual void accept(TypeVisitor &v) const = 0;
    protected:
        UnitFactory &factory;
        TypeSquared typeType;
    };

    class IntegerType : public Type {
    public:
        explicit IntegerType(UnitFactory &factory) : Type(factory, INT_TYPE) {};
        IntegerType(const IntegerType&) = delete;

        virtual unsigned int width() const = 0; //returns width of integer in bytes
        void accept(TypeVisitor &v) const override;
    };

    class ObjectType: public Type {
    public:
        explicit ObjectType(UnitFactory &factory) : Type(factory, OBJECT_TYPE) {};
        ObjectType(const ObjectType&) = delete;
        void accept(TypeVisitor &v) const override;
    };

    class MapType: public Type {
    public:
        explicit MapType(UnitFactory &factory) : Type(factory, MAP_TYPE) {};
        MapType(const MapType&) = delete;

        virtual Type* keyType() const = 0;
        virtual Type* valueType() const = 0;
        void accept(TypeVisitor &v) const override;
    };

    class ArrayType: public Type {
    public:
        explicit ArrayType(UnitFactory &factory) : Type(factory, ARRAY_TYPE) {};
        ArrayType(const ArrayType&) = delete;

        virtual bool isDynamic() const = 0;
        virtual Type* baseType() const = 0;
        virtual uint64_t length() const = 0;
        void accept(TypeVisitor &v) const override;
    };

    class PointerType: public Type{
    public:
        explicit PointerType(UnitFactory &factory) : Type(factory, POINTER_TYPE ) {};
        PointerType(const PointerType&) = delete;

        //bool isOpaque();
        virtual Type* referencedType() const = 0;
        void accept(TypeVisitor &v) const override;
    };

    class StructType: public Type{
    public:
        explicit StructType(UnitFactory &factory) : Type(factory, STRUCT_TYPE) {};
        StructType(const StructType&) = delete;

        virtual unsigned int numFields() = 0;
        virtual std::list<Type*> fieldTypes() = 0;
        void accept(TypeVisitor &v) const override;
    };

    class VoidType: public Type{
    public:
        explicit VoidType(UnitFactory &factory) : Type(factory, VOID_TYPE) {};
        VoidType(const VoidType&) = delete;
        void accept(TypeVisitor &v) const override;
    };

    class LocationType: public Type{
    public:
        explicit  LocationType(UnitFactory &factory) : Type(factory, LOCATION_TYPE) {};
        LocationType(const LocationType&) = delete;
        void accept(TypeVisitor &v) const override;
    };

    class UnknownType : public Type {
    public:
        explicit UnknownType(UnitFactory &factory) : Type(factory, UNKNOWN_TYPE) {};
        UnknownType(const UnknownType&) = delete;
        void accept(TypeVisitor &v) const override;
    };

    class TypeVisitor {
    public:
        virtual void commonVisit(const Type &v) {};
        virtual void visit(const IntegerType &v) { commonVisit(v); };
        virtual void visit(const ObjectType &v) { commonVisit(v); };
        virtual void visit(const MapType &v) { commonVisit(v); };
        virtual void visit(const ArrayType &v) { commonVisit(v); };
        virtual void visit(const PointerType &v) { commonVisit(v); };
        virtual void visit(const StructType &v) { commonVisit(v); };
        virtual void visit(const VoidType &v) { commonVisit(v); };
        virtual void visit(const LocationType &v) { commonVisit(v); };
        virtual void visit(const UnknownType &v) { commonVisit(v); };
    };



    /*class IntegerType: public Type{
        public:
            explicit IntegerType(UnitFactory &factory, const llvm::IntegerType&);

            IntegerType(const IntegerType&) = delete;

            unsigned width(); //returns width of integer in bytes

            std::string name() const override;

            const llvm::IntegerType &unwrap();

        private:
            const llvm::IntegerType& integer;
    };

    class ArrayType: public Type{
        public:
            explicit ArrayType(UnitFactory &factory, const llvm::ArrayType&);

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
            explicit PointerType(UnitFactory &factory, const llvm::PointerType& pointer);

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
            explicit StructType(UnitFactory &factory, const llvm::StructType& structT);

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
            explicit VectorType(UnitFactory &factory, const llvm::VectorType& vector);

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
            explicit VoidType(UnitFactory &factory, const llvm::Type&);

            VoidType(const VoidType&) = delete;

            std::string name() const override;

            const llvm::Type &unwrap();

        private:
            const llvm::Type& voidType;
    };

    class LabelType: public Type{
    public:
        explicit  LabelType(UnitFactory &factory, const llvm::Type&);

        LabelType(const LabelType&) = delete;

        std::string name() const override;

        const llvm::Type &unwrap();

    private:
        const llvm::Type& labelType;
    };*/
}

#endif