//
// Created by Jon Stephens on 3/28/22.
//

#include "RegisterVal.h"

namespace vanguard {
    RegisterVal::RegisterVal(const Value &v) : val(v) {}

    ValType RegisterVal::type() const {
        return REG_VAL;
    }

    const Value &RegisterVal::reg() const {
        return val;
    }

    bool operator==(const RegisterVal &lhs, const RegisterVal &rhs) {
        return &lhs.val == &rhs.val;
    }
}