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
#include <unordered_map>

namespace vanguard {
    class TaintSummary : public TaintSinkProvider {
    public:
        TaintSummary(const Function &summaryFn, ReadWriteRetriever &rw, const std::vector<FunctionTaintSink *> &fnSinks, const std::vector<FunctionTaintSource *> &fnSources, llvm::AAResults &aa);
        ~TaintSummary();
        bool propagate(const llvm::Instruction &ins);
        std::vector<TaintNode *> getTaint(FunctionTaintSink &sink) override;
        bool didSummaryChange();
    private:
        std::vector<TaintLabel *> getOrCreateTaintLabels(Taint *state, std::vector<Val *> &vals);
        Taint *getPrevTaint(const llvm::Instruction &ins);
        bool computeSummary();

        llvm::AAResults &alias;
        ReadWriteRetriever &rwRetriever;
        const Function &fn;
        TaintLabelStore labelStore;
        std::unordered_map<RegisterVal, uint64_t> regTaint;
        std::unordered_map<const BasicBlock *, Taint *> bbInit;
        std::unordered_map<const Instruction *, Taint *> insToTaint;
        std::vector<FunctionTaintSource *> fnSources;
        //std::unordered_map<RegisterVal, TaintLabel *> valToLabel;
        std::unordered_map<Val *, TaintLabel *, ValPtrHash, ValPtrEq> valToLabel;
        Taint *initState;
        Taint *summary;
    };
}



#endif //VANGUARD_TAINTSUMMARY_H
