//
// Created by Jon Stephens on 3/30/22.
//

#include "TaintSummaryStore.h"


namespace vanguard {
    TaintSummaryStore::TaintSummaryStore(std::vector<FunctionTaintSink *> &sinks, std::vector<FunctionTaintSource *> &sources) : fnSinks(sinks), fnSources(sources) {

    }

    TaintSummary *TaintSummaryStore::getSummary(const Function &fn) {
        auto summaryIt = fnSummaries.find(&fn);
        TaintSummary *summary = nullptr;
        if(summaryIt == fnSummaries.end()) {
            summary = new TaintSummary(fn, rwRetriever, fnSinks, fnSources);
            fnSummaries[&fn] = summary;
        }
        else {
            summary = summaryIt->second;
        }

        return summary;
    }
}