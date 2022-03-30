//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_TAINT_H
#define VANGUARD_TAINT_H

#include "llvm/IR/Function.h"
#include "Val.h"
#include "RegisterVal.h"
#include "TaintLabel.h"
#include <unordered_map>
#include <vector>
using namespace llvm;


/*
 * Plan: Each function can define up to 64 taint labels.
 * Each sink will take in those taint labels that reach the sink.
 * Each taint label will register taint sources that reach those labels.
 *     - This will allow us to use taint summaries in the following way: if an arg was tainted simply add a taint source
 *       to the argument that corresponds to the taint source.
 */

namespace vanguard {
    class Taint {
    public:
        Taint(TaintLabelStore &labelStore, std::unordered_map<RegisterVal, uint64_t> &sharedRegTaint);
        bool isTainted(const Val &v) const;
        bool isTainted(const Val &v, const TaintLabel &label) const;

        bool addTaint(const Val &v, const TaintLabel &label);
        bool untaint(const Val &v, const TaintLabel &label);
        bool untaint(const Val &v);
        std::vector<TaintLabel *> taintedWith(const Val &v) const;

        static bool propagate(const Taint &from, const std::vector<Val> &uses, Taint &to, const std::vector<Val> &tgts);
        static bool merge(const std::vector<Taint *> &from, Taint &to);
    private:
        std::unordered_map<RegisterVal, uint64_t> &regTaint;
        TaintLabelStore &labelStore;

        uint64_t getTaint(const Val &v) const;
        uint64_t accumulate(const std::vector<Val> &vals) const;
        bool setTaint(const Val &v, uint64_t mask);
        bool addTaint(const Val &v, uint64_t mask);
        bool untaint(const Val &v, uint64_t mask);
    };
}



#endif //VANGUARD_TAINT_H
