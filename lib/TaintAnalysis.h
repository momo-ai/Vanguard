//
// Created by Jon Stephens on 3/18/22.
//

#ifndef VANGUARD_TAINTANALYSIS_H
#define VANGUARD_TAINTANALYSIS_H
#include "ReachAnalysis.h"
#include "llvm/IR/Function.h"
#include "Taint.h"
#include "ReadWriteRetriever.h"
#include "FunctionTaintSource.h"
#include "FunctionTaintSink.h"
#include "TaintSummaryStore.h"
#include "AARequirement.h"


//Taint analysis should be agnostic what we're running on (i.e. intraprocedural / functional)

namespace vanguard {
    class TaintAnalysis : public ReachAnalysis {
    public:
        TaintAnalysis(blockchain::AAWrapper &aa, std::vector<FunctionTaintSink *> &sinks, std::vector<FunctionTaintSource *> &sources);
        ~TaintAnalysis();
        void startAnalysis() override;
        bool transfer(Instruction &ins) override;
        bool beginFn(Function &fn) override;
        bool endFn(Function &fn) override;

    protected:
        std::vector<FunctionTaintSink *> sinks;
        std::vector<FunctionTaintSource *> sources;
    private:
        blockchain::AAWrapper &alias;
        TaintSummaryStore *store;
        TaintSummary *curSummary;
    };
}



#endif //VANGUARD_TAINTANALYSIS_H
