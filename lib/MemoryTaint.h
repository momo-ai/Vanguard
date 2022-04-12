//
// Created by Jon Stephens on 3/31/22.
//

#ifndef VANGUARD_MEMORYTAINT_H
#define VANGUARD_MEMORYTAINT_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Value.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "MemoryVal.h"
#include <unordered_map>
#include <AAWrapper.h>

namespace vanguard {
    class MemoryTaint {
    public:
        explicit MemoryTaint(llvm::Function &taintFn, blockchain::AAWrapper &aa);

        //static bool propagate(const Taint &from, const std::vector<Val *> &uses, Taint &to, const std::vector<Val *> &tgts);
        //static bool merge(const std::vector<Taint *> &from, Taint &to);
    protected:
        std::vector<std::pair<const MemoryVal *, uint64_t>> getMemTaint() const;

    private:
        blockchain::AAWrapper &aaWrapper;
        llvm::Function &fn;

        /*
         * For now we're just going to do something quick and dirty. Get by checking for alias against all memory taint
         * and set by applying labels to all memoryvals that are aliased. There might be duplicates (i.e. size not correct)
         */
        std::unordered_map<MemoryVal, uint64_t> memTaint;

        friend MemoryVal;

        //hide implementation details as much as possible
        bool addMemTaint(const MemoryVal &v, uint64_t mask);
        bool untaintMem(const MemoryVal &v, uint64_t mask);
        uint64_t getMemTaint(const MemoryVal &v) const;
        bool setMemTaint(const MemoryVal &v, uint64_t mask);
    };
}





#endif //VANGUARD_MEMORYTAINT_H
