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
        ~TaintAnalysis();
        void startAnalysis(llvm::Pass &pass) override;
        void registerRequirements(llvm::AnalysisUsage &Info) const override;
        bool transfer(Instruction &ins) override;
        bool beginFn(Function &fn) override;
        bool endFn(Function &fn) override;

    private:
        std::vector<FunctionTaintSink *> sinks;
        std::vector<FunctionTaintSource *> sources;
        TaintSummaryStore *store;
        TaintSummary *curSummary;
    };
}



#endif //VANGUARD_TAINTANALYSIS_H
