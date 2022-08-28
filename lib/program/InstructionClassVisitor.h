//
// Created by Jon Stephens on 8/26/22.
//

#ifndef VANGUARD_INSTRUCTIONCLASSVISITOR_H
#define VANGUARD_INSTRUCTIONCLASSVISITOR_H

#include "InstructionClasses.h"

namespace vanguard {
    class InstructionClassVisitor{
    public:
        virtual void visit(const Branch &v) = 0;
        virtual void visit(const Return &v) = 0;
        virtual void visit(const Error &v) = 0;
        virtual void visit(const BinaryOpExpr &v) = 0;
        virtual void visit(const UnaryOpExpr &v) = 0;
        virtual void visit(const CallExpr &v) = 0;
        virtual void visit(const CastExpr &v) = 0;
        virtual void visit(const TernaryExpr &v) = 0;
        virtual void visit(const Assignment &v) = 0;
        virtual void visit(const UnknownExpr &v) = 0;
    };
}

#endif //VANGUARD_INSTRUCTIONCLASSVISITOR_H
