//
// Created by Jon Stephens on 9/2/22.
//

#ifndef VANGUARD_INSTRUCTIONTRANS_H
#define VANGUARD_INSTRUCTIONTRANS_H

#include <program/InstructionClassVisitor.h>
#include <string>
#include "ValueTrans.h"

namespace vanguard {
    class InstructionTrans: public InstructionClassVisitor{
    public:
        std::string getValueString(const Value &v){
            ValueTrans trans;
            v.accept(trans);
            return trans.result;
        }

        std::string result;
        void visit(const BinaryOpExpr<Universe> &inst) override{
            auto op = inst.op();
            auto varResult = inst.result();
            result = "BinaryIns of BinaryOpClass " + std::to_string(op) + " has LHS: " + getValueString(*varResult) + " and operands: ";
            auto n = inst.numOperands();
            assert(n == 2 && "BinaryIns does not have 2 operands");
            result += getValueString(*inst.operand(0)) + " and ";
            result += getValueString(*inst.operand(1));
        }

        void visit(const Branch<Universe> &inst) override{
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
                    result += getValueString(*inst.operand(i)) + " ";
                }
            }
        }

        void visit(const UnaryOpExpr<Universe> &inst) override{
            result = "UnaryIns of UnaryOpClass " + std::to_string(inst.op()) + " has operand " +
                     getValueString(*inst.operand());
        }

        void visit(const CastExpr<Universe> &inst) override{
            result = "CastIns casts to " + inst.castTo()->name() ;
        }

        void visit(const CallExpr<Universe> &inst) override{
            result = "Call to function " + inst.target()->name() + " with arguments: ";
            auto args = inst.args();
            for (auto arg: args){
                result += getValueString(*arg) + ", ";
            }
        }

        void visit(const Error<Universe> &inst) override {
            result = "UnreachableIns: " + inst.msg() ;
        }

        void visit(const Return<Universe> &inst) override {
            result = "ReturnIns ";
            if (inst.returnsValue()){
                result += "returns value " + getValueString(*inst.value());
            }
            else{
                result += "not returning a value.";
            }
        }

        void visit(const TernaryExpr<Universe> &inst) override{
            result = "SelectIns with condition " + getValueString(*inst.condition()) + " has true Value " +
                     getValueString(*inst.trueValue()) + " and false value " + getValueString(*inst.falseValue());
        }

        void visit(const Assignment<Universe> &inst) override {
            result = "assigns " + getValueString(*inst.result());
        }

        void visit(const UnknownExpr<Universe> &inst) override {
            result = "Unknown expression";
        }
    };
}
#endif //VANGUARD_INSTRUCTIONTRANS_H
