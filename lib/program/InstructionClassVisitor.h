//
// Created by Jon Stephens on 8/26/22.
//

#ifndef VANGUARD_INSTRUCTIONCLASSVISITOR_H
#define VANGUARD_INSTRUCTIONCLASSVISITOR_H

#include "InstructionClasses.h"

namespace vanguard {
    class InstructionClassVisitor{
    public:
        virtual void visit(const Branch &v) {};
        virtual void visit(const Return &v) {};
        virtual void visit(const Error &v) {};
        virtual void visit(const BinaryOpExpr &v) {};
        virtual void visit(const UnaryOpExpr &v) {};
        virtual void visit(const CallExpr &v) {};
        virtual void visit(const CastExpr &v) {};
        virtual void visit(const TernaryExpr &v) {};
        virtual void visit(const Assignment &v) {};
        virtual void visit(const UnknownExpr &v) {};
    };
}

#endif //VANGUARD_INSTRUCTIONCLASSVISITOR_H
