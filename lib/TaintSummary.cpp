//
// Created by Jon Stephens on 3/29/22.
//

#include "TaintSummary.h"


namespace vanguard {
    TaintSummary::TaintSummary(const Function &summaryFn, ReadWriteInfo &rw) : fn(summaryFn), rwInfo(rw) {}


}