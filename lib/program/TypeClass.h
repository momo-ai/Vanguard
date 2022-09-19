//
// Created by Jon Stephens on 9/17/22.
//

#ifndef VANGUARD_TYPECLASS_H
#define VANGUARD_TYPECLASS_H

#include <list>

namespace vanguard {
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

    template<typename Domain> class TypeVisitor;

    template<typename Domain>
    class IntegerType : public Domain::Type {
    public:
        template<typename ...Args>
        explicit IntegerType(Args&&... args) : Domain::Type(std::forward<Args>(args)..., INT_TYPE) {};
        IntegerType(const IntegerType&) = delete;

        virtual unsigned int width() const = 0; //returns width of integer in bytes
        void accept(TypeVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class ObjectType: public Domain::Type {
    public:
        template<typename ...Args>
        explicit ObjectType(Args&&... args) : Domain::Type(std::forward<Args>(args)..., OBJECT_TYPE) {};
        ObjectType(const ObjectType&) = delete;
        void accept(TypeVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class MapType: public Domain::Type {
    public:
        template<typename ...Args>
        explicit MapType(Args&&... args) : Domain::Type(std::forward<Args>(args)..., MAP_TYPE) {};
        MapType(const MapType&) = delete;

        virtual typename Domain::Type* keyType() const = 0;
        virtual typename Domain::Type* valueType() const = 0;
        void accept(TypeVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class ArrayType: public Domain::Type {
    public:
        template<typename ...Args>
        explicit ArrayType(Args&&... args) : Domain::Type(std::forward<Args>(args)..., ARRAY_TYPE) {};
        ArrayType(const ArrayType&) = delete;

        virtual bool isDynamic() const = 0;
        virtual typename Domain::Type* baseType() const = 0;
        virtual uint64_t length() const = 0;
        void accept(TypeVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class PointerType: public Domain::Type{
    public:
        template<typename ...Args>
        explicit PointerType(Args&&... args) : Domain::Type(std::forward<Args>(args)..., POINTER_TYPE) {};
        PointerType(const PointerType&) = delete;

        //bool isOpaque();
        virtual typename Domain::Type* referencedType() const = 0;
        void accept(TypeVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class StructType: public Domain::Type{
    public:
        template<typename ...Args>
        explicit StructType(Args&&... args) : Domain::Type(std::forward<Args>(args)..., STRUCT_TYPE) {};
        StructType(const StructType&) = delete;

        virtual unsigned int numFields() = 0;
        virtual std::list<typename Domain::Type*> fieldTypes() = 0;
        void accept(TypeVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class VoidType: public Domain::Type{
    public:
        template<typename ...Args>
        explicit VoidType(Args&&... args) : Domain::Type(std::forward<Args>(args)..., VOID_TYPE) {};
        VoidType(const VoidType&) = delete;
        void accept(TypeVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class LocationType: public Domain::Type{
    public:
        template<typename ...Args>
        explicit LocationType(Args&&... args) : Domain::Type(std::forward<Args>(args)..., LOCATION_TYPE) {};
        LocationType(const LocationType&) = delete;
        void accept(TypeVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class UnknownType : public Domain::Type {
    public:
        template<typename ...Args>
        explicit UnknownType(Args&&... args) : Domain::Type(std::forward<Args>(args)..., UNKNOWN_TYPE) {};
        UnknownType(const UnknownType&) = delete;
        void accept(TypeVisitor<Domain> &v) const override {
            v.visit(*this);
        }
    };

    template<typename Domain>
    class TypeVisitor {
    public:
        virtual void commonVisit(const typename Domain::Type &v) {};
        virtual void visit(const IntegerType<Domain> &v) { commonVisit(v); };
        virtual void visit(const ObjectType<Domain> &v) { commonVisit(v); };
        virtual void visit(const MapType<Domain> &v) { commonVisit(v); };
        virtual void visit(const ArrayType<Domain> &v) { commonVisit(v); };
        virtual void visit(const PointerType<Domain> &v) { commonVisit(v); };
        virtual void visit(const StructType<Domain> &v) { commonVisit(v); };
        virtual void visit(const VoidType<Domain> &v) { commonVisit(v); };
        virtual void visit(const LocationType<Domain> &v) { commonVisit(v); };
        virtual void visit(const UnknownType<Domain> &v) { commonVisit(v); };
    };
}

#endif //VANGUARD_TYPECLASS_H
