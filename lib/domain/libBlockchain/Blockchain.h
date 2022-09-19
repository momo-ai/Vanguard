//
// Created by Jon Stephens on 8/31/22.
//

#ifndef VANGUARD_BLOCKCHAIN_H
#define VANGUARD_BLOCKCHAIN_H

#include <utility>
#include <iostream>

enum Mutability {
    PURE,
    VIEW,
    PAYABLE,
    NONPAYABLE
};

enum Visibility {
    EXTERNAL,
    PUBLIC,
    INTERNAL,
    PRIVATE,
    DEFAULT
};

namespace vanguard {
    template<class Base, class Domain>
    class Blockchain : public Base {
    public:
        class Universe;
        class Factory;
        class Contract;
        class CompilationUnit;
        class Function;

        class Instruction;
        template<typename Wrap, typename D = void> class CallIns;

        class Type;
        template<typename Wrap, typename D = void> class BlkArrayType;
        template<typename Wrap, typename D = void> class BlkMapType;
        template<typename Wrap, typename D = void> class BlkStructType;

        class Value;
        template<typename Wrap, typename D = void> class BlkVariable;
    };
}



#endif //VANGUARD_BLOCKCHAIN_H
