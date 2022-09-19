//
// Created by Jon Stephens on 9/18/22.
//

#ifndef VANGUARD_LIBBLOCKCHAIN_TYPE_H
#define VANGUARD_LIBBLOCKCHAIN_TYPE_H

#include "Blockchain.h"
#include <string>

namespace vanguard {
    template<class Base, class Domain>
    class Blockchain<Base, Domain>::Type : public Base::Type {
    public:
        template<typename ...Args>
        explicit Type( Args&&... args) : Base::Type(std::forward<Args>(args)...) {};

    private:
    };

    template<class Base, class Domain>
    template<typename Wrap, typename D>
    class Blockchain<Base, Domain>::BlkArrayType : public Base::template ArrayType<Wrap, D> {
    public:
        template<typename ...Args>
        BlkArrayType(typename Domain::Type *baseType, Args&&... args) : base(baseType), len((uint64_t)(-1)), dynamic(true), Base::template ArrayType<Wrap, D>(std::forward<Args>(args)...) {};

        template<typename ...Args>
        BlkArrayType(typename Domain::Type *baseType, uint64_t len, Args&&... args) : base(baseType), len(len), dynamic(false), Base::template ArrayType<Wrap, D>(std::forward<Args>(args)...) {};

        bool isDynamic() const override {
            return dynamic;
        }

        typename Domain::Type* baseType() const override {
            return base;
        }

        uint64_t length() const override {
            return len;
        }
    private:
        bool dynamic;
        typename Domain::Type *base;
        uint64_t len;
    };

    template<class Base, class Domain>
    template<typename Wrap, typename D>
    class Blockchain<Base, Domain>::BlkMapType : public Base::template MapType<Wrap, D> {
    public:
        template<typename ...Args>
        BlkMapType(typename Domain::Type *keyType, typename Domain::Type* valType, Args&&... args) : key(keyType), val(valType), Base::template MapType<Wrap, D>(std::forward<Args>(args)...) {};

        typename Domain::Type* keyType() const override {
            return key;
        }

        typename Domain::Type* valueType() const override {
            return val;
        }
    private:
        typename Domain::Type* key;
        typename Domain::Type* val;
    };

    template<class Base, class Domain>
    template<typename Wrap, typename D>
    class Blockchain<Base, Domain>::BlkStructType : public Base::template StructType<Wrap, D> {
    public:
        template<typename ...Args>
        explicit BlkStructType(std::vector<vanguard::Variable<Domain> *> fields, Args&&... args) : structFields(std::move(fields)), Base::template StructType<Wrap, D>(std::forward<Args>(args)...) {};

        unsigned int numFields() override {
            return structFields.size();
        }

        virtual std::vector<vanguard::Variable<Domain> *> fields() {
            return structFields;
        }

        std::list<typename Domain::Type*> fieldTypes() override {
            std::list<typename Domain::Type*> types;

            for(auto field : structFields) {
                types.push_back(field->type());
            }

            return types;
        }

    private:
        std::vector<vanguard::Variable<Domain> *> structFields;
    };
}
#endif //VANGUARD_TYPE_H
