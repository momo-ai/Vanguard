//
// Created by Jon Stephens on 3/18/22.
//

#ifndef VANGUARD_TAINTANALYSIS_H
#define VANGUARD_TAINTANALYSIS_H
#include "Analysis.h"
#include "llvm/IR/Function.h"
#include "Taint.h"
#include "ReadWriteRetriever.h"
#include "FunctionTaintSource.h"
#include "FunctionTaintSink.h"
#include "TaintSummaryStore.h"


//Taint analysis should be agnostic what we're running on (i.e. intraprocedural / functional)

namespace vanguard {
    class TaintAnalysis : public Analysis {
    public:
        TaintAnalysis(std::vector<FunctionTaintSink *> &sinks, std::vector<FunctionTaintSource *> &sources);
        bool transfer(const Instruction &ins) override;
        bool beginFn(const Function &fn) override;
        bool endFn(const Function &fn) override;

    private:
        TaintSummaryStore store;
        TaintSummary *curSummary;
    };
}



#endif //VANGUARD_TAINTANALYSIS_H
