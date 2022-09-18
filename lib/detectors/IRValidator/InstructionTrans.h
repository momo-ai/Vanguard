//
// Created by Jon Stephens on 9/2/22.
//

#ifndef VANGUARD_INSTRUCTIONTRANS_H
#define VANGUARD_INSTRUCTIONTRANS_H

#include <program/InstructionClasses.h>
#include <program/InstructionClassVisitor.h>
#include <string>
#include "ValueTrans.h"

namespace vanguard {
    template<typename Domain>
    class InstructionTrans: public InstructionClassVisitor<Domain>{
    public:
        std::string getValueString(const typename Domain::Value &v){
            ValueTrans<Domain> trans;
            v.accept(trans);
            return trans.result;
        }

        std::string result;
        void visit(const BinaryOpIns<Domain> &inst) override{
            auto op = inst.op();
            auto varResult = inst.result();
            result = "BinaryIns of BinaryOpClass " + std::to_string(op) + " has LHS: " + getValueString(*varResult) + " and operands: ";
            auto n = inst.numOperands();
            assert(n == 2 && "BinaryIns does not have 2 operands");
            result += getValueString(*inst.operandAt(0)) + " and ";
            result += getValueString(*inst.operandAt(1));
        }

        void visit(const BranchIns<Domain> &inst) override{
            result = "BranchIns ";
            if (inst.isConditional()){
                result+= "with condition " + getValueString(*inst.condition()) + ", ";
            }
            result += " has successors: ";
            for (auto blk : inst.targets()){
                result += blk->name() + ", ";
            }
            auto n = inst.numOperands();
            if (n != 0) {
                result += "and operands ";
                for (int i = 0; i < n; i++) {
                    result += getValueString(*inst.operandAt(i)) + " ";
                }
            }
        }

        void visit(const UnaryOpIns<Domain> &inst) override{
            result = "UnaryIns of UnaryOpClass " + std::to_string(inst.op()) + " has operand " +
                     getValueString(*inst.operand());
        }

        void visit(const CastIns<Domain> &inst) override{
            result = "CastIns casts to " + inst.castTo()->name() ;
        }

        void visit(const CallIns<Domain> &inst) override{
            auto tgts = inst.targets();
            assert(tgts.size() > 0);

            for(auto tgt : tgts) {
                result = "Call to function " + tgt->name() + " with arguments: ";
                auto args = inst.args();
                for (auto arg: args){
                    result += getValueString(*arg) + ", ";
                }
            }

        }

        void visit(const ErrorIns<Domain> &inst) override {
            result = "UnreachableIns: " + inst.msg() ;
        }

        void visit(const ReturnIns<Domain> &inst) override {
            result = "ReturnIns ";
            if (inst.returnsValue()){
                result += "returns value " + getValueString(*inst.value());
            }
            else{
                result += "not returning a value.";
            }
        }

        void visit(const TernaryIns<Domain> &inst) override{
            result = "SelectIns with condition " + getValueString(*inst.condition()) + " has true Value " +
                     getValueString(*inst.trueValue()) + " and false value " + getValueString(*inst.falseValue());
        }

        void visit(const AssignIns<Domain> &inst) override {
            result = "assigns " + getValueString(*inst.result());
        }

        void visit(const UnknownIns<Domain> &inst) override {
            result = "Unknown expression";
        }
    };
}
#endif //VANGUARD_INSTRUCTIONTRANS_H
