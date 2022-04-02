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
        explicit RegisterTaint(std::unordered_map<RegisterVal, uint64_t> &sharedRegTaint);
        /*bool isTainted(const RegisterVal &v) const;
        bool isTainted(const RegisterVal &v, const TaintLabel &label) const;

        bool addTaint(const RegisterVal &v, const TaintLabel &label);
        bool untaint(const RegisterVal &v, const TaintLabel &label);
        bool untaint(const RegisterVal &v);
        std::vector<TaintLabel *> taintedWith(const RegisterVal &v) const;*/


        //static bool propagate(const Taint &from, const std::vector<Val *> &uses, Taint &to, const std::vector<Val *> &tgts);
        //static bool merge(const std::vector<Taint *> &from, Taint &to);
    protected:
        std::vector<std::pair<const RegisterVal *, uint64_t>> getRegTaint();

    private:
        friend RegisterVal;

        std::unordered_map<RegisterVal, uint64_t> &regTaint;

        //hide implementation details as much as possible
        bool addRegTaint(const RegisterVal &v, uint64_t mask);
        bool untaintReg(const RegisterVal &v, uint64_t mask);
        uint64_t getRegTaint(const RegisterVal &v) const;
        bool setRegTaint(const RegisterVal &v, uint64_t mask);
    };
}
#endif //VANGUARD_REGISTERTAINT_H
