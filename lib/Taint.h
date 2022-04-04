//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_TAINT_H
#define VANGUARD_TAINT_H

#include "llvm/IR/Function.h"
#include "Val.h"
#include "RegisterVal.h"
#include "TaintLabel.h"
#include "RegisterTaint.h"
#include "MemoryTaint.h"
#include <unordered_map>
#include <vector>
using namespace llvm;

#include "llvm/Analysis/AliasAnalysis.h"
/*
 * Plan: Each function can define up to 64 taint labels.
 * Each sink will take in those taint labels that reach the sink.
 * Each taint label will register taint sources that reach those labels.
 *     - This will allow us to use taint summaries in the following way: if an arg was tainted simply add a taint source
 *       to the argument that corresponds to the taint source.
 */

namespace vanguard {
    class Taint : public RegisterTaint, public MemoryTaint {
    public:
        Taint(TaintLabelStore &labelStore, std::unordered_map<RegisterVal, uint64_t> &sharedRegTaint, AAWrapper &alias);

        bool isTainted(const Val &v) const;
        bool isTainted(const Val &v, const TaintLabel &label) const;

        bool addTaint(const Val &v, const TaintLabel &label);
        bool untaint(const Val &v, const TaintLabel &label);
        bool untaint(const Val &v);
        std::vector<TaintLabel *> taintedWith(const Val &v) const;

        bool propagate(const Taint &from, const std::vector<Val *> &uses, const std::vector<Val *> &tgts);
        bool merge(const std::vector<Taint *> &from);

        bool hasValLabel(Val &val);
        std::vector<TaintLabel *> getOrCreateTaintLabels(std::vector<Val *> &vals);
        TaintLabel *getOrCreateTaintLabel(Val &val);
        bool isTaintedWith(const Val &v, std::unordered_set<const TaintLabel *> labels) const;
    private:
        TaintLabelStore &store;
        uint64_t accumulate(const std::vector<Val *> &vals) const;
        std::vector<std::pair<const Val *, uint64_t>> getAllTaint() const;
        std::unordered_map<Val *, TaintLabel *, ValPtrHash, ValPtrEq> valToLabel;
    };
}


/*namespace vanguard {
    class Taint {
    public:
        Taint(TaintLabelStore &labelStore, std::unordered_map<RegisterVal, uint64_t> &sharedRegTaint);
        bool isTainted(const Val &v) const;
        bool isTainted(const Val &v, const TaintLabel &label) const;

        bool addTaint(const Val &v, const TaintLabel &label);
        bool untaint(const Val &v, const TaintLabel &label);
        bool untaint(const Val &v);
        std::vector<TaintLabel *> taintedWith(const Val &v) const;

        static bool propagate(const Taint &from, const std::vector<Val *> &uses, Taint &to, const std::vector<Val *> &tgts);
        static bool merge(const std::vector<Taint *> &from, Taint &to);
    private:
        std::unordered_map<RegisterVal, uint64_t> &regTaint;
        TaintLabelStore &labelStore;

        uint64_t getTaint(const Val &v) const;
        uint64_t accumulate(const std::vector<Val *> &vals) const;
        bool setTaint(const Val &v, uint64_t mask);
        bool addTaint(const Val &v, uint64_t mask);
        bool untaint(const Val &v, uint64_t mask);
    };
}*/



#endif //VANGUARD_TAINT_H
