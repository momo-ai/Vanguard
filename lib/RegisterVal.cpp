//
// Created by Jon Stephens on 3/28/22.
//

#include "RegisterVal.h"
#include "Taint.h"

namespace vanguard {
    RegisterVal::RegisterVal(const Value &v) : Val(ValType::REGISTER_VAL), val(&v) {}

    const Value &RegisterVal::reg() const {
        return *val;
    }

    bool operator==(const RegisterVal &lhs, const RegisterVal &rhs) {
        return lhs.val == rhs.val;
    }

    /*
     * Overloaded Functions
     */

    bool RegisterVal::operator==(const Val &rhs) const {
        if(isa<const RegisterVal>(rhs)) {
            auto &v = cast<const RegisterVal>(rhs);
            return *this == v;
        }

        return false;
    }

    std::size_t RegisterVal::hash() const {
        return (size_t) val;
    }

    bool RegisterVal::isTainted(Taint &taint) const {
        return taint.isTainted(*this);
    }

    bool RegisterVal::isTainted(Taint &taint, const TaintLabel &label) const {
        return taint.isTainted(*this, label);
    }

    bool RegisterVal::addTaint(Taint &taint, const TaintLabel &label) const {
        return taint.addTaint(*this, label);
    }

    bool RegisterVal::untaint(Taint &taint) const {
        return taint.untaint(*this);
    }

    bool RegisterVal::untaint(Taint &taint, const TaintLabel &label) const {
        return taint.untaint(*this, label);
    }

    std::vector<TaintLabel *> RegisterVal::taintedWith(Taint &taint) const {
        return taint.taintedWith(*this);
    }

    uint64_t RegisterVal::getTaint(const Taint &taint) const {
        return taint.getTaint(*this);
    }
    bool RegisterVal::setTaint(Taint &taint, uint64_t mask) const {
        return taint.setTaint(*this, mask);
    }
    bool RegisterVal::addTaint(Taint &taint, uint64_t mask) const {
        return taint.addTaint(*this, mask);
    }
}