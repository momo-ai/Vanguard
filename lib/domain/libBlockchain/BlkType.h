//
// Created by Jon Stephens on 9/2/22.
//

#ifndef VANGUARD_BLKTYPE_H
#define VANGUARD_BLKTYPE_H

#include <program/Type.h>
#include <program/Value.h>

#include <utility>

namespace vanguard {
    template <typename Base>
    class BlkType : public Base {
    public:
        template<typename ...Args>
        explicit BlkType(std::string name, Args&&... args) : typeName(std::move(name)), Base(std::forward<Args>(args)...) {};

        std::string name() const override {
            return typeName;
        }
    private:
        std::string typeName;
    };

    template <typename Base>
    class BlkArrayType : public BlkType<Base> {
    public:
        template<typename ...Args>
        BlkArrayType(Type *baseType, Args&&... args) : base(baseType), len((uint64_t)(-1)), dynamic(true), BlkType<Base>(std::forward<Args>(args)...) {};

        template<typename ...Args>
        BlkArrayType(Type *baseType, uint64_t len, Args&&... args) : base(baseType), len(len), dynamic(false), BlkType<Base>(std::forward<Args>(args)...) {};

        bool isDynamic() const override {
            return dynamic;
        }

        Type* baseType() const override {
            return base;
        }

        uint64_t length() const override {
            return len;
        }
    private:
        bool dynamic;
        Type *base;
        uint64_t len;
    };

    template <typename Base>
    class BlkMapType : public BlkType<Base> {
    public:
        template<typename ...Args>
        BlkMapType(Type *keyType, Type* valType, Args&&... args) : key(keyType), val(valType), BlkType<Base>(std::forward<Args>(args)...) {};

        Type* keyType() const {
            return key;
        }

        Type* valueType() const {
            return val;
        }
    private:
        Type* key;
        Type* val;
    };

    template <typename Base>
    class BlkStructType : public BlkType<Base> {
    public:
        template<typename ...Args>
        explicit BlkStructType(std::vector<Variable *> fields, Args&&... args) : structFields(std::move(fields)), BlkType<Base>(std::forward<Args>(args)...) {};

        unsigned int numFields() override {
            return structFields.size();
        }

        virtual std::vector<Variable *> fields() {
            return structFields;
        }

        std::list<Type*> fieldTypes() override {
            std::list<Type*> types;

            for(auto field : structFields) {
                types.push_back(field->type());
            }

            return types;
        }

    private:
        std::vector<Variable *> structFields;
    };
}

#endif //VANGUARD_BLKTYPE_H
