//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_TAINT_H
#define VANGUARD_TAINT_H

#include "llvm/IR/Value.h"
using namespace llvm;

namespace vanguard {
    class Taint {
    public:
        virtual bool isTainted(Value &v);
        virtual int taintLabel(Value &v) = 0;
        virtual bool taint(Value &v, int label) = 0;

    };
}



#endif //VANGUARD_TAINT_H
