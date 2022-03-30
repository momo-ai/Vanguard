//
// Created by Jon Stephens on 3/28/22.
//

#ifndef VANGUARD_REGISTERVAL_H
#define VANGUARD_REGISTERVAL_H

#include "llvm/IR/Value.h"
#include "Val.h"

using namespace llvm;

namespace vanguard {
    class RegisterVal : public Val {
    public:
        explicit RegisterVal(const Value &v);
        ValType type() const override;
        friend bool operator==(const RegisterVal& lhs, const RegisterVal& rhs);
        const Value &reg() const;
    private:
        const Value &val;
    };
}

namespace std {
    template <>
    struct hash<vanguard::RegisterVal>
    {
        std::size_t operator()(const vanguard::RegisterVal & t) const
        {
            return (size_t) &t.reg();
        }
    };
}

#endif //VANGUARD_REGISTERVAL_H
