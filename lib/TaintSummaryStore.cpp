//
// Created by Jon Stephens on 3/30/22.
//

#include "TaintSummaryStore.h"
#include "AAWrapper.h"


using namespace blockchain;

namespace vanguard {
    TaintSummaryStore::TaintSummaryStore(std::vector<FunctionTaintSink *> &sinks, std::vector<FunctionTaintSource *> &sources, AAWrapper &alias) : fnSinks(sinks), fnSources(sources), alias(alias) {

    }

    TaintSummary *TaintSummaryStore::getSummary(Function &fn) {
        auto summaryIt = fnSummaries.find(&fn);
        TaintSummary *summary = nullptr;
        if(summaryIt == fnSummaries.end()) {
            /*AAResults *alias = nullptr;

            if(!fn.isDeclaration()) {
                alias = &pass.getAnalysis<AAResultsWrapperPass>(fn).getAAResults();
            }*/
            summary = new TaintSummary(*this, fn, rwRetriever, fnSinks, fnSources, alias);
            fnSummaries[&fn] = summary;
        }
        else {
            summary = summaryIt->second;
        }

        return summary;
    }
}