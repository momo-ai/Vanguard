//
// Created by Jon Stephens on 3/28/22.
//

#ifndef VANGUARD_VAL_H
#define VANGUARD_VAL_H

#include <llvm/IR/Function.h>
#include <unordered_set>
#include <vector>

namespace vanguard {
    enum ValType {
        REG_VAL,
        MEM_VAL
    };

    class Val {
    public:
        virtual ~Val() = default;
        virtual ValType type() const = 0;
        static std::vector<Val *> functionOutputs(const llvm::Function &fn);
        static std::vector<Val *> functionArgs(const llvm::Function &fn);
    };
}

#endif //VANGUARD_VAL_H
