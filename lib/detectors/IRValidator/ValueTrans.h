//
// Created by Jon Stephens on 9/2/22.
//

#ifndef VANGUARD_VALUETRANS_H
#define VANGUARD_VALUETRANS_H

#include <string>
#include <program/Value.h>


namespace vanguard {
    class ValueTrans : public ValueClassVisitor{
    public:
        std::string result;

        void visit(const Variable &v) override{
            if (v.hasName()){
                result = "GlobalVariable " + v.name() + " of type " + v.type()->name();
            }
            else {
                result = "GlobalVariable of type " + v.type()->name();
            }
            result += ", ";
        }

        void visit(const Literal &v) override{
            result  = "IntegerLiteral of type " + v.type()->name() + " and value: ";
        }


        void visit(const Pointer &v) override {
            result = "found pointer";
        }

        void visit(const MemoryRegion &v) override{
            result = "MemoryRegion of type " + v.type()->name(); // + " and size " + std::to_string(v.size()) + ", ";
        }

        void visit(const Constant &v) override{
            result = "Constant of type " + v.type()->name();
        }

        void visit(const Location &v) override{
            result = "BlockValue of type " +
                     v.type()->name();
        }
    };
}

#endif //VANGUARD_VALUETRANS_H
