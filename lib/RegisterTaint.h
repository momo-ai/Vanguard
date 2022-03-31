//
// Created by Jon Stephens on 3/31/22.
//

#ifndef VANGUARD_REGISTERTAINT_H
#define VANGUARD_REGISTERTAINT_H

#include "TaintLabelStore.h"
#include "RegisterVal.h"

namespace vanguard {
    class RegisterTaint {
    public:
        RegisterTaint(TaintLabelStore &labelStore, std::unordered_map<RegisterVal, uint64_t> &sharedRegTaint);
        bool isTainted(const RegisterVal &v) const;
        bool isTainted(const RegisterVal &v, const TaintLabel &label) const;

        bool addTaint(const RegisterVal &v, const TaintLabel &label);
        bool untaint(const RegisterVal &v, const TaintLabel &label);
        bool untaint(const RegisterVal &v);
        std::vector<TaintLabel *> taintedWith(const RegisterVal &v) const;


        //static bool propagate(const Taint &from, const std::vector<Val *> &uses, Taint &to, const std::vector<Val *> &tgts);
        //static bool merge(const std::vector<Taint *> &from, Taint &to);
    protected:
        std::vector<std::pair<const RegisterVal *, uint64_t>> getRegTaint();

    private:
        friend RegisterVal;

        std::unordered_map<RegisterVal, uint64_t> &regTaint;
        TaintLabelStore &labelStore;

        //hide implementation details as much as possible
        bool addTaint(const RegisterVal &v, uint64_t mask);
        bool untaint(const RegisterVal &v, uint64_t mask);
        uint64_t getTaint(const RegisterVal &v) const;
        bool setTaint(const RegisterVal &v, uint64_t mask);
    };
}
#endif //VANGUARD_REGISTERTAINT_H
