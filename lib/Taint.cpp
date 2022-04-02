//
// Created by Jon Stephens on 3/19/22.
//

#include <unordered_set>
#include "Taint.h"

namespace vanguard {
    Taint::Taint(TaintLabelStore &store, std::unordered_map<RegisterVal, uint64_t> &sharedRegTaint, AAWrapper &alias) : store(store), RegisterTaint(sharedRegTaint), MemoryTaint(alias) {}

    bool Taint::isTainted(const Val &v) const {
        return v.getTaint(*this) != 0;
    }

    bool Taint::isTainted(const Val &v, const TaintLabel &label) const {
        return (v.getTaint(*this) & label.taintMask()) != 0;
    }

    bool Taint::addTaint(const Val &v, const TaintLabel &label) {
        return v.addTaint(*this, label.taintMask());
    }

    bool Taint::untaint(const Val &v, const TaintLabel &label) {
        return v.untaint(*this, label.taintMask());
    }

    bool Taint::untaint(const Val &v) {
        return v.untaint(*this, v.getTaint(*this));
    }

    std::vector<TaintLabel *> Taint::taintedWith(const Val &v) const {
        uint64_t valTaint = v.getTaint(*this);
        std::vector<TaintLabel *> taintLabels;

        while(valTaint != 0) {
            uint64_t mask = valTaint & -((int64_t) valTaint);
            valTaint -= mask;
            TaintLabel *label = store.getLabelFromMask(mask);
            taintLabels.push_back(label);
        }

        return taintLabels;
    }

    bool Taint::propagate(const Taint &from, const std::vector<Val *> &uses, const std::vector<Val *> &tgts) {
        uint64_t taint = from.accumulate(uses);
        bool modified = false;

        for(auto v : tgts) {
            //modified = to.setTaint(*v, taint) || modified;
            modified = v->setTaint(*this, taint);
        }

        return modified;
    }

    bool Taint::merge(const std::vector<Taint *> &from) {
        if(from.empty()) {
            return false;
        }

        bool modified = false;
        for(auto cur : from) {
            for(auto &entry : getAllTaint()) {
                modified = entry.first->addTaint(*this, entry.second) || modified;
            }
            /*for(auto &entry : (*cur).regTaint) {
                modified = this->addTaint(entry.first, entry.second) || modified;
            }*/
        }

        return modified;
    }

    std::vector<std::pair<const Val *, uint64_t>> Taint::getAllTaint() {
        std::vector<std::pair<const Val *, uint64_t>> allTaint;
        std::vector<std::pair<const RegisterVal *, uint64_t>> regTaint = getRegTaint();
        allTaint.insert(allTaint.end(), regTaint.begin(), regTaint.end());
        return allTaint;
    }

    /*
     * Private helpers
     */
    uint64_t Taint::accumulate(const std::vector<Val *> &from) const {
        uint64_t accTaint = 0;
        for(auto v : from) {
            accTaint = accTaint | v->getTaint(*this);
        }

        return accTaint;
    }

    /*bool Taint::setTaint(const Val &v, uint64_t mask) {
        if(v.type() == ValType::REG_VAL) {
            const auto &regVal = static_cast<const RegisterVal &>(v);

            if(regTaint[regVal] == mask) {
                return false;
            }

            regTaint[regVal] = mask;
            return true;
        }

        return false;
    }

    bool Taint::addTaint(const Val &v, uint64_t mask) {
        if(v.type() == ValType::REG_VAL) {
            const auto &regVal = static_cast<const RegisterVal &>(v);

            if((regTaint[regVal] & mask) == mask) {
                return false;
            }

            regTaint[regVal] |= mask;
            return true;
        }

        return false;
    }

    bool Taint::untaint(const Val &v, uint64_t mask) {
        if(v.type() == ValType::REG_VAL) {
            const auto &regVal = static_cast<const RegisterVal &>(v);

            if((regTaint[regVal] & mask) == 0) {
                return false;
            }

            regTaint[regVal] &= ~mask;
            return true;
        }

        return false;
    }

    uint64_t Taint::getTaint(const Val &v) const {
        if(v.type() == ValType::REG_VAL) {
            const auto &regVal = static_cast<const RegisterVal &>(v);
            if(regTaint.find(regVal) == regTaint.end()) {
                return 0;
            }

            return regTaint.at(regVal);
        }

        return 0;
    }*/

    /*
     * Public Functions
     */

    /*bool Taint::isTainted(const Val &v) const {
        return getTaint(v) != 0;
    }

    bool Taint::isTainted(const Val &v, const TaintLabel &label) const {
        return (getTaint(v) & label.taintMask()) != 0;
    }

    bool Taint::addTaint(const Val &v, const TaintLabel &label) {
        return addTaint(v, label.taintMask());
    }

    bool Taint::untaint(const Val &v, const TaintLabel &label) {
        return untaint(v, label.taintMask());
    }

    bool Taint::untaint(const Val &v) {
        return untaint(v, getTaint(v));
    }

    std::vector<TaintLabel *> Taint::taintedWith(const Val &v) const {
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

}