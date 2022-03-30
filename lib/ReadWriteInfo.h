//
// Created by Jon Stephens on 3/28/22.
//

#ifndef VANGUARD_READWRITEINFO_H
#define VANGUARD_READWRITEINFO_H

#include "llvm/IR/Instruction.h"
#include "llvm/IR/InstVisitor.h"
#include "Val.h"
#include <vector>

using namespace llvm;

namespace vanguard {
    class ReadWriteInfo : public InstVisitor<ReadWriteInfo> {
    public:
        //std::vector<Val> reads(const Instruction &ins);
        //std::vector<Val> writes(const Instruction &ins);
    };
}



#endif //VANGUARD_READWRITEINFO_H
