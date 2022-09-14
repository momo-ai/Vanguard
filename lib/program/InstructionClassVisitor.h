//
// Created by Jon Stephens on 8/26/22.
//

#ifndef VANGUARD_INSTRUCTIONCLASSVISITOR_H
#define VANGUARD_INSTRUCTIONCLASSVISITOR_H


namespace vanguard {
    template<typename Base> class BranchIns;
    template<typename Base> class ReturnIns;
    template<typename Base> class ErrorIns;
    template<typename Base> class AssignIns;
    template<typename Base> class BinaryOpIns;
    template<typename Base> class UnaryOpIns;
    template<typename Base> class CallIns;
    template<typename Base> class CastIns;
    template<typename Base> class TernaryIns;
    template<typename Base> class UnknownIns;

    template<typename Base>
    class InstructionClassVisitor{
    public:
        virtual void visit(const BranchIns<Base> &v) {};
        virtual void visit(const ReturnIns<Base> &v) {};
        virtual void visit(const ErrorIns<Base> &v) {};
        virtual void visit(const BinaryOpIns<Base> &v) {};
        virtual void visit(const UnaryOpIns<Base> &v) {};
        virtual void visit(const CallIns<Base> &v) {};
        virtual void visit(const CastIns<Base> &v) {};
        virtual void visit(const TernaryIns<Base> &v) {};
        virtual void visit(const AssignIns<Base> &v) {};
        virtual void visit(const UnknownIns<Base> &v) {};
    };
}

#endif //VANGUARD_INSTRUCTIONCLASSVISITOR_H
