//
// Created by Jon Stephens on 3/30/22.
//

#include "TaintSummaryStore.h"


namespace vanguard {
    TaintSummaryStore::TaintSummaryStore(std::vector<FunctionTaintSink *> &sinks, std::vector<FunctionTaintSource *> &sources, llvm::Pass &pass) : fnSinks(sinks), fnSources(sources), pass(pass) {

    }

    TaintSummary *TaintSummaryStore::getSummary(Function &fn) {
        auto summaryIt = fnSummaries.find(&fn);
        TaintSummary *summary = nullptr;
        if(summaryIt == fnSummaries.end()) {
            if(fn.isDeclaration()) {
                return nullptr;
            }
            auto &alias = pass.getAnalysis<AAResultsWrapperPass>(fn).getAAResults();
            summary = new TaintSummary(fn, rwRetriever, fnSinks, fnSources, alias);
            fnSummaries[&fn] = summary;
        }
        else {
            summary = summaryIt->second;
        }

        return summary;
    }
}