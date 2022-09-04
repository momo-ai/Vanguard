//
// Created by Jon Stephens on 8/26/22.
//

#ifndef VANGUARD_INSTRUCTIONCLASSVISITOR_H
#define VANGUARD_INSTRUCTIONCLASSVISITOR_H

#include "InstructionClasses.h"

namespace vanguard {
    template<typename Domain>
    class InstructionClassVisitor{
    public:
        virtual void visit(const Branch<Domain> &v) {};
        virtual void visit(const Return<Domain> &v) {};
        virtual void visit(const Error<Domain> &v) {};
        virtual void visit(const BinaryOpExpr<Domain> &v) {};
        virtual void visit(const UnaryOpExpr<Domain> &v) {};
        virtual void visit(const CallExpr<Domain> &v) {};
        virtual void visit(const CastExpr<Domain> &v) {};
        virtual void visit(const TernaryExpr<Domain> &v) {};
        virtual void visit(const Assignment<Domain> &v) {};
        virtual void visit(const UnknownExpr<Domain> &v) {};
    };
}

#endif //VANGUARD_INSTRUCTIONCLASSVISITOR_H
