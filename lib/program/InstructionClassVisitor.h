//
// Created by Jon Stephens on 8/26/22.
//

#ifndef VANGUARD_INSTRUCTIONCLASSVISITOR_H
#define VANGUARD_INSTRUCTIONCLASSVISITOR_H


namespace vanguard {
    template<typename Base> class Branch;
    template<typename Base> class Return;
    template<typename Base> class Error;
    template<typename Base> class Expression;
    template<typename Base> class Assignment;
    template<typename Base> class BinaryOpExpr;
    template<typename Base> class UnaryOpExpr;
    template<typename Base> class CallExpr;
    template<typename Base> class CastExpr;
    template<typename Base> class TernaryExpr;
    template<typename Base> class UnknownExpr;

    template<typename Base>
    class InstructionClassVisitor{
    public:
        virtual void visit(const Branch<Base> &v) {};
        virtual void visit(const Return<Base> &v) {};
        virtual void visit(const Error<Base> &v) {};
        virtual void visit(const BinaryOpExpr<Base> &v) {};
        virtual void visit(const UnaryOpExpr<Base> &v) {};
        virtual void visit(const CallExpr<Base> &v) {};
        virtual void visit(const CastExpr<Base> &v) {};
        virtual void visit(const TernaryExpr<Base> &v) {};
        virtual void visit(const Assignment<Base> &v) {};
        virtual void visit(const UnknownExpr<Base> &v) {};
    };
}

#endif //VANGUARD_INSTRUCTIONCLASSVISITOR_H
