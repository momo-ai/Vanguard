//
// Created by Jon Stephens on 8/26/22.
//

#ifndef VANGUARD_INSTRUCTIONCLASSVISITOR_H
#define VANGUARD_INSTRUCTIONCLASSVISITOR_H


namespace vanguard {
    template<typename Domain> class BranchIns;
    template<typename Domain> class ReturnIns;
    template<typename Domain> class ErrorIns;
    template<typename Domain> class AssignIns;
    template<typename Domain> class BinaryOpIns;
    template<typename Domain> class UnaryOpIns;
    template<typename Domain> class CallIns;
    template<typename Domain> class CastIns;
    template<typename Domain> class TernaryIns;
    template<typename Domain> class UnknownIns;

    template<typename Domain>
    class InstructionClassVisitor{
    public:
        virtual void visit(const BranchIns<Domain> &v) {};
        virtual void visit(const ReturnIns<Domain> &v) {};
        virtual void visit(const ErrorIns<Domain> &v) {};
        virtual void visit(const BinaryOpIns<Domain> &v) {};
        virtual void visit(const UnaryOpIns<Domain> &v) {};
        virtual void visit(const CallIns<Domain> &v) {};
        virtual void visit(const CastIns<Domain> &v) {};
        virtual void visit(const TernaryIns<Domain> &v) {};
        virtual void visit(const AssignIns<Domain> &v) {};
        virtual void visit(const UnknownIns<Domain> &v) {};
    };
}

#endif //VANGUARD_INSTRUCTIONCLASSVISITOR_H
