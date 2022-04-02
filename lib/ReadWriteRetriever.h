//
// Created by Jon Stephens on 3/28/22.
//

#ifndef VANGUARD_READWRITERETRIEVER_H
#define VANGUARD_READWRITERETRIEVER_H

#include "llvm/IR/Instruction.h"
#include "llvm/IR/InstVisitor.h"
#include "Val.h"
#include <vector>

using namespace llvm;

namespace vanguard {

    struct ReadWriteInfo {
        bool requiresUpdate;
        std::vector<Val *> reads;
        std::vector<Val *> writes;

        ~ReadWriteInfo();
    };

    class ReadWriteRetriever : public InstVisitor<ReadWriteRetriever> {
    public:
        ReadWriteInfo retrieve(const Instruction &ins);
    private:
        ReadWriteInfo get(const LoadInst &ins);
        ReadWriteInfo get(const StoreInst &ins);
        ReadWriteInfo get(const Instruction &ins);
    };
}



#endif //VANGUARD_READWRITERETRIEVER_H
