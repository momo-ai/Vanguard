//
// Created by Jon Stephens on 3/29/22.
//

#ifndef VANGUARD_TAINTSUMMARY_H
#define VANGUARD_TAINTSUMMARY_H

#include "Taint.h"
#include "TaintLabelStore.h"
#include "llvm/IR/Function.h"
#include "ReadWriteInfo.h"

namespace vanguard {
    class TaintSummary {
        TaintSummary(const Function &summaryFn, ReadWriteInfo &rw);


    private:
        const ReadWriteInfo &rwInfo;
        const Function &fn;
        TaintLabelStore labelStore;
        std::unordered_map<RegisterVal, uint64_t> regTaint;
    };
}



#endif //VANGUARD_TAINTSUMMARY_H
