//
// Created by Jon Stephens on 3/29/22.
//

#ifndef VANGUARD_TAINTSUMMARY_H
#define VANGUARD_TAINTSUMMARY_H

#include "Taint.h"
#include "TaintLabelStore.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "ReadWriteRetriever.h"
#include "FunctionTaintSink.h"
#include "FunctionTaintSource.h"
#include "TaintSinkProvider.h"
#include <AAWrapper.h>
#include <unordered_map>

namespace vanguard {
    class TaintSummaryStore;
    class TaintSummary : public TaintSinkProvider {
    public:
        TaintSummary(TaintSummaryStore &parent, Function &summaryFn, ReadWriteRetriever &rw, const std::vector<FunctionTaintSink *> &fnSinks, const std::vector<FunctionTaintSource *> &fnSources, blockchain::AAWrapper &alias);
        ~TaintSummary();
        bool propagate(const llvm::Instruction &ins);
        bool propagate(const llvm::CallInst &call);
        std::vector<TaintNode *> getTaint(const FunctionTaintSink &sink) const override;
        bool didSummaryChange();
        blockchain::AAWrapper &getAliasWrapper();
        const Function &function() const;
        const TaintSummaryStore &parent();
        bool isGenerated(const TaintLabel *) const;
    private:
        Taint *getPrevTaint(const llvm::Instruction &ins);
        bool computeSummary();

        //labels created within the function

        std::unordered_set<const TaintLabel *> generatedLabels;
        std::vector<TaintLabel *> getOrCreateTaintLabels(std::vector<std::pair<FunctionLocation, Val *>> &vals);
        TaintSummaryStore &store;
        blockchain::AAWrapper &alias;
        ReadWriteRetriever &rwRetriever;
        Function &fn;
        TaintLabelStore labelStore;
        std::unordered_map<RegisterVal, uint64_t> regTaint;
        std::unordered_map<const BasicBlock *, Taint *> bbInit;
        std::unordered_map<const Instruction *, Taint *> insToTaint;
        std::vector<FunctionTaintSource *> fnSources;
        //std::unordered_map<RegisterVal, TaintLabel *> valToLabel;
        Taint *initState;
        Taint *summary;
    };
}



#endif //VANGUARD_TAINTSUMMARY_H
