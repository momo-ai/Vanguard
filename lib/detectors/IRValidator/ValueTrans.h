//
// Created by Jon Stephens on 9/2/22.
//

#ifndef VANGUARD_VALUETRANS_H
#define VANGUARD_VALUETRANS_H

#include <string>
#include <program/Value.h>


namespace vanguard {
    template<typename Domain>
    class ValueTrans : public ValueClassVisitor<Domain> {
    public:
        std::string result;

        void visit(const Variable<Domain> &v) override{
            if (v.hasName()){
                result = "GlobalVariable " + v.name() + " of type " + v.type()->name();
            }
            else {
                result = "GlobalVariable of type " + v.type()->name();
            }
            result += ", ";
        }

        void visit(const Literal<Domain> &v) override{
            result  = "IntegerLiteral of type " + v.type()->name() + " and value: ";
        }


        void visit(const Pointer<Domain> &v) override {
            result = "found pointer";
        }

        void visit(const MemoryRegion<Domain> &v) override{
            result = "MemoryRegion of type " + v.type()->name(); // + " and size " + std::to_string(v.size()) + ", ";
        }

        void visit(const Constant<Domain> &v) override{
            result = "Constant of type " + v.type()->name();
        }

        void visit(const Location<Domain> &v) override{
            result = "BlockValue of type " +
                     v.type()->name();
        }
    };
}

#endif //VANGUARD_VALUETRANS_H
