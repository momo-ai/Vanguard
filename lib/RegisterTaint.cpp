//
// Created by Jon Stephens on 3/31/22.
//

#include "RegisterTaint.h"

//
// Created by Jon Stephens on 3/19/22.
//

#include <unordered_set>

namespace vanguard {
    RegisterTaint::RegisterTaint(std::unordered_map<RegisterVal, uint64_t> &sharedRegTaint) : regTaint(sharedRegTaint) {}
    /*
     * Private helpers
     */
    /*uint64_t RegisterTaint::accumulate(const std::vector<Val *> &from) const {
        uint64_t accTaint = 0;
        for(auto &v : from) {
            accTaint = accTaint | getTaint(*v);
        }

        return accTaint;
    }*/

    bool RegisterTaint::setRegTaint(const RegisterVal &v, uint64_t mask) {
        const auto &regVal = static_cast<const RegisterVal &>(v);

        if(regTaint[regVal] == mask) {
            return false;
        }

        regTaint[regVal] = mask;
        return true;
    }

    bool RegisterTaint::addRegTaint(const RegisterVal &v, uint64_t mask) {
        const auto &regVal = static_cast<const RegisterVal &>(v);

        if((regTaint[regVal] & mask) == mask) {
            return false;
        }

        regTaint[regVal] |= mask;
        return true;
    }

    bool RegisterTaint::untaintReg(const RegisterVal &v, uint64_t mask) {
        const auto &regVal = static_cast<const RegisterVal &>(v);

        if((regTaint[regVal] & mask) == 0) {
            return false;
        }

        regTaint[regVal] &= ~mask;
        return true;
    }

    uint64_t RegisterTaint::getRegTaint(const RegisterVal &v) const {
        const auto &regVal = static_cast<const RegisterVal &>(v);
        if(regTaint.find(regVal) == regTaint.end()) {
            return 0;
        }
        return regTaint.at(regVal);
    }

    /*
     * Public Functions
     */

    /*bool RegisterTaint::isTainted(const RegisterVal &v) const {
        return getTaint(v) != 0;
    }

    bool RegisterTaint::isTainted(const RegisterVal &v, const TaintLabel &label) const {
        return (getTaint(v) & label.taintMask()) != 0;
    }

    bool RegisterTaint::addTaint(const RegisterVal &v, const TaintLabel &label) {
        return addTaint(v, label.taintMask());
    }

    bool RegisterTaint::untaint(const RegisterVal &v, const TaintLabel &label) {
        return untaint(v, label.taintMask());
    }

    bool RegisterTaint::untaint(const RegisterVal &v) {
        return untaint(v, getTaint(v));
    }

    std::vector<TaintLabel *> RegisterTaint::taintedWith(const RegisterVal &v) const {
        uint64_t valTaint = getTaint(v);
        std::vector<TaintLabel *> taintLabels;

        while(valTaint != 0) {
            uint64_t mask = valTaint & -((int64_t) valTaint);
            valTaint -= mask;
            TaintLabel *label = labelStore.getLabelFromMask(mask);
            taintLabels.push_back(label);
        }

        return taintLabels;
    }*/

    std::vector<std::pair<const RegisterVal *, uint64_t>> RegisterTaint::getRegTaint() {
        std::vector<std::pair<const RegisterVal *, uint64_t>> tainted;

        for(auto &entry : regTaint) {
            tainted.emplace_back(&entry.first, entry.second);
        }

        return tainted;
    }

    /*bool Taint::propagate(const Taint &from, const std::vector<Val *> &uses, Taint &to, const std::vector<Val *> &tgts) {
        uint64_t taint = from.accumulate(uses);
        bool modified = false;

        for(auto v : tgts) {
            modified = to.setTaint(*v, taint) || modified;
        }

        return modified;
    }

    bool Taint::merge(const std::vector<Taint *> &from, Taint &to) {
        if(from.empty()) {
            return false;
        }

        bool modified = false;
        for(auto cur : from) {
            for(auto &entry : (*cur).regTaint) {
                modified = to.addTaint(entry.first, entry.second) || modified;
            }
        }

        return modified;
    }*/
}