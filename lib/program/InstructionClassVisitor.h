//
// Created by Jon Stephens on 8/26/22.
//

#ifndef VANGUARD_INSTRUCTIONCLASSVISITOR_H
#define VANGUARD_INSTRUCTIONCLASSVISITOR_H

#include "InstructionClasses.h"

namespace vanguard {
    class InstructionClassVisitor{
    public:
        virtual void visit(const Branch<Universe> &v) {};
        virtual void visit(const Return<Universe> &v) {};
        virtual void visit(const Error<Universe> &v) {};
        virtual void visit(const BinaryOpExpr<Universe> &v) {};
        virtual void visit(const UnaryOpExpr<Universe> &v) {};
        virtual void visit(const CallExpr<Universe> &v) {};
        virtual void visit(const CastExpr<Universe> &v) {};
        virtual void visit(const TernaryExpr<Universe> &v) {};
        virtual void visit(const Assignment<Universe> &v) {};
        virtual void visit(const UnknownExpr<Universe> &v) {};
    };
}

#endif //VANGUARD_INSTRUCTIONCLASSVISITOR_H
