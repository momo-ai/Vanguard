//
// Created by Jon Stephens on 3/28/22.
//

#ifndef VANGUARD_VAL_H
#define VANGUARD_VAL_H

#include <llvm/IR/Function.h>
#include <unordered_set>

namespace vanguard {
    enum ValType {
        REG_VAL,
        MEM_VAL
    };

    class Val {
    public:
        virtual ~Val() = default;
        virtual ValType type() const = 0;
        static std::unordered_set<Val *> functionOutputs(llvm::Function &fn);
    };
}

#endif //VANGUARD_VAL_H
