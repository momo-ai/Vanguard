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
        friend bool operator==(const RegisterVal& lhs, const RegisterVal& rhs);
        const Value &reg() const;

        /*Connecting to llvm's casting infrastructure*/
        static inline bool classof(const RegisterVal *) { return true; }
        static inline bool classof(const Val *b) {
            if(b->getType() == REGISTER_VAL) { return true; }
            return false;
        }

        //overloaded fns
        bool operator==(const Val &rhs) const override;
        std::size_t hash() const override;
        bool isTainted(Taint &taint) const override;
        bool isTainted(Taint &taint, const TaintLabel &label) const override;
        bool addTaint(Taint &taint, const TaintLabel &label) const override;
        bool untaint(Taint &taint) const override;
        bool untaint(Taint &taint, const TaintLabel &label) const override;
        std::vector<TaintLabel *> taintedWith(Taint &taint) const override;
    private:
        const Value *val;

        uint64_t getTaint(const Taint &taint) const override;
        bool setTaint(Taint &taint, uint64_t mask) const override;
        bool addTaint(Taint &taint, uint64_t mask) const override;
    };
}

namespace std {
    template <>
    struct hash<vanguard::RegisterVal>
    {
        std::size_t operator()(const vanguard::RegisterVal & t) const
        {
            return t.hash();
        }
    };
}

#endif //VANGUARD_REGISTERVAL_H
