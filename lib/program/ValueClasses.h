//
// Created by Jon Stephens on 9/16/22.
//

#ifndef VANGUARD_VALUECLASSES_H
#define VANGUARD_VALUECLASSES_H

#include "Type.h"

namespace vanguard{
    enum ValueClassEnum{
        VARIABLE,
        CONSTANT,
        LITERAL,
        POINTER,
        MEMORY_REGION,
        LOCATION,
    };

    template<typename Domain> class ValueClassVisitor;

    template<typename Domain>
    class Variable : public Domain::Value {
    public:
        explicit Variable(typename Domain::Factory &factory) : Domain::Value(factory, VARIABLE) {};

        static inline bool classof(const Variable &) { return true; }
        static inline bool classof(const Variable *) { return true; }
        static inline bool classof(const typename Domain::Value *value) { return classof(*value); }
        static inline bool classof(const typename Domain::Value &value) {
            if (value.valueClass() == VARIABLE){ return true; }
            return false;
        }

        virtual bool hasName() const = 0;
        virtual std::string name() const = 0;
        void accept(ValueClassVisitor<Domain> &v) const override {
            return v.visit(*this);
        }
    };

    template<typename Domain>
    class Constant : public Domain::Value {
    public:
        explicit Constant(typename Domain::Factory &factory) : Domain::Value(factory, CONSTANT) {};
        static inline bool classof(const Constant &) { return true; }
        static inline bool classof(const Constant *) { return true; }
        static inline bool classof(const typename Domain::Value *value) { return classof(*value); }
        static inline bool classof(const typename Domain::Value &value) {
            if (value.valueClass() == CONSTANT){ return true; }
            return false;
        }
        void accept(ValueClassVisitor<Domain> &v) const override {
            return v.visit(*this);
        }
    };

    template<typename Domain>
    class Literal : public Domain::Value {
    public:
        explicit Literal(typename Domain::Factory &factory) : Domain::Value(factory, LITERAL) {};
        static inline bool classof(const Literal &) { return true; }
        static inline bool classof(const Literal *) { return true; }
        static inline bool classof(const typename Domain::Value *value) { return classof(*value); }
        static inline bool classof(const typename Domain::Value &value) {
            if (value.valueClass() == LITERAL){ return true; }
            return false;
        }

        //virtual LitType value() const = 0;
        void accept(ValueClassVisitor<Domain> &v) const override {
            return v.visit(*this);
        }
    };

    template<typename Domain>
    class Pointer : public Domain::Value {
    public:
        explicit Pointer(typename Domain::Factory &factory) : Domain::Value(factory, POINTER) {};
        static inline bool classof(const Pointer &) { return true; }
        static inline bool classof(const Pointer *) { return true; }
        static inline bool classof(const typename Domain::Value *value) { return classof(*value); }
        static inline bool classof(const typename Domain::Value &value) {
            if (value.valueClass() == POINTER){ return true; }
            return false;
        }

        virtual typename Domain::Value *base() const = 0;
        virtual typename Domain::Value *offset() const = 0;
        //virtual Type *refType() const = 0;
        void accept(ValueClassVisitor<Domain> &v) const override {
            return v.visit(*this);
        }
    };

    template<typename Domain>
    class MemoryRegion : public Domain::Value {
    public:
        explicit MemoryRegion(typename Domain::Factory &factory) : Domain::Value(factory, MEMORY_REGION) {};
        static inline bool classof(const MemoryRegion &) { return true; }
        static inline bool classof(const MemoryRegion *) { return true; }
        static inline bool classof(const typename Domain::Value *value) { return classof(*value); }
        static inline bool classof(const typename Domain::Value &value) {
            if (value.valueClass() == MEMORY_REGION){ return true; }
            return false;
        }

        /*virtual const Pointer *pointer() const = 0;
        virtual unsigned long size() const = 0;*/
        void accept(ValueClassVisitor<Domain> &v) const override {
            return v.visit(*this);
        }
    };

    template<typename Domain>
    class Location : public Domain::Value {
    public:
        explicit Location(typename Domain::Factory &factory) : Domain::Value(factory, LOCATION) {};
        static inline bool classof(const Location &) { return true; }
        static inline bool classof(const Location *) { return true; }
        static inline bool classof(const typename Domain::Value *value) { return classof(*value); }
        static inline bool classof(const typename Domain::Value &value) {
            if (value.valueClass() == LOCATION){ return true; }
            return false;
        }

        virtual typename Domain::Block &loc() const = 0;
        void accept(ValueClassVisitor<Domain> &v) const override {
            return v.visit(*this);
        }
    };

    template<typename Domain>
    class ValueClassVisitor{
    public:
        virtual void visit(const Variable<Domain> &v) = 0;
        virtual void visit(const Constant<Domain> &v) = 0;
        virtual void visit(const Literal<Domain> &v) = 0;
        virtual void visit(const Pointer<Domain> &v) = 0;
        virtual void visit(const MemoryRegion<Domain> &v) = 0;
        virtual void visit(const Location<Domain> &v) = 0;
    };
}


#endif //VANGUARD_VALUECLASSES_H
