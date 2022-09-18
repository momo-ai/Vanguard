//
// Created by Jon Stephens on 8/20/22.
//

#ifndef VANGUARD_BASE_H
#define VANGUARD_BASE_H

#include <vector>
#include <llvm/IR/Module.h>
#include <list>
#include <unordered_set>
#include "InstructionClassVisitor.h"

namespace vanguard {
    enum InstructionClassEnum {
        BRANCH,
        RETURN,
        ERROR,
        EXPRESSION_BEGIN,
        BIN_OP = EXPRESSION_BEGIN,
        UN_OP,
        CALL,
        CAST,
        TERNARY,
        ASSIGNMENT,
        UNKNOWN,
        EXPRESSION_END = UNKNOWN
    };

    template<typename Domain> class Variable;

    template <typename Domain>
    class Base {
    public:
        class Universe;
        class Factory;
        class CompilationUnit;
        class Function;
        class Block;
        class Instruction;
        template<typename Wrap, typename D = void> class BranchIns;
        template<typename Wrap, typename D = void> class ReturnIns;
        template<typename Wrap, typename D = void> class ErrorIns;
        template<typename Wrap, typename D = void> class AssignIns;
        template<typename Wrap, typename D = void> class BinaryOpIns;
        template<typename Wrap, typename D = void> class UnaryOpIns;
        template<typename Wrap, typename D = void> class CallIns;
        template<typename Wrap, typename D = void> class CastIns;
        template<typename Wrap, typename D = void> class TernaryIns;
        template<typename Wrap, typename D = void> class UnknownIns;

        class Value;
        template<typename Wrap, typename D = void> class Variable;
        template<typename Wrap, typename D = void> class Constant;
        template<typename Wrap, typename D = void> class Literal;
        template<typename Wrap, typename D = void> class Pointer;
        template<typename Wrap, typename D = void> class MemoryRegion;
        template<typename Wrap, typename D = void> class Location;

        class Type;
        template<typename Wrap, typename D = void> class IntegerType;
        template<typename Wrap, typename D = void> class ArrayType;
        template<typename Wrap, typename D = void> class MapType;
        //template<typename Wrap, typename D = void> class VectorType;
        template<typename Wrap, typename D = void> class PointerType;
        template<typename Wrap, typename D = void> class StructType;
        template<typename Wrap, typename D = void> class VoidType;
        template<typename Wrap, typename D = void> class LocationType;
    };
}



#endif //VANGUARD_BASE_H
