//
// Created by Jon Stephens on 3/30/22.
//

#ifndef VANGUARD_TAINTSUMMARYSTORE_H
#define VANGUARD_TAINTSUMMARYSTORE_H


#include "FunctionTaintSink.h"
#include "FunctionTaintSource.h"
#include <vector>
#include "llvm/IR/Function.h"
#include "TaintSummary.h"

namespace vanguard {
    class ReadWriteRetriever;

    class TaintSummaryStore {
    public:
        TaintSummaryStore(std::vector<FunctionTaintSink *> &sinks, std::vector<FunctionTaintSource *> &sources, blockchain::AAWrapper &alias);
        TaintSummary *getSummary(Function &fn);
    private:
        blockchain::AAWrapper &alias;
        std::vector<FunctionTaintSink *> fnSinks;
        std::vector<FunctionTaintSource *> fnSources;
        ReadWriteRetriever rwRetriever;
        std::unordered_map<const Function *, TaintSummary *> fnSummaries;
    };
}



#endif //VANGUARD_TAINTSUMMARYSTORE_H
