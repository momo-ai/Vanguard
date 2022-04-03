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
#include "AAWrapper.h"
#include <unordered_map>

namespace vanguard {
    class TaintSummaryStore;
    class TaintSummary : public TaintSinkProvider {
    public:
        TaintSummary(TaintSummaryStore &parent, Function &summaryFn, ReadWriteRetriever &rw, const std::vector<FunctionTaintSink *> &fnSinks, const std::vector<FunctionTaintSource *> &fnSources, llvm::Pass &pass);
        ~TaintSummary();
        bool propagate(const llvm::Instruction &ins);
        bool propagate(const llvm::CallInst &call);
        std::vector<TaintNode *> getTaint(FunctionTaintSink &sink) override;
        bool didSummaryChange();
        AAWrapper &getAliasWrapper();
        const Function &function() const;
        const TaintSummaryStore &parent();
    private:
        Taint *getPrevTaint(const llvm::Instruction &ins);
        bool computeSummary();

        //labels created within the function
        std::unordered_set<TaintLabel *> generatedLabels;
        std::vector<TaintLabel *> getOrCreateTaintLabels(std::vector<std::pair<FunctionLocation, Val *>> &vals);
        TaintSummaryStore &store;
        AAWrapper alias;
        ReadWriteRetriever &rwRetriever;
        const Function &fn;
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
