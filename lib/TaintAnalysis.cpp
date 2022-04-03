//
// Created by Jon Stephens on 3/18/22.
//

#include <iostream>
#include "TaintAnalysis.h"
#include "llvm/Analysis/AliasAnalysis.h"

namespace vanguard {

    TaintAnalysis::TaintAnalysis(std::vector<FunctionTaintSink *> &sinks, std::vector<FunctionTaintSource *> &sources) : sinks(sinks), sources(sources), store(nullptr) {

    }

    TaintAnalysis::~TaintAnalysis() {
        delete store;
    }

    void TaintAnalysis::registerRequirements(llvm::AnalysisUsage &info) const {
        info.addRequired<AAResultsWrapperPass>();
    }

    void TaintAnalysis::startAnalysis(llvm::Pass &pass) {
        store = new TaintSummaryStore(sinks, sources, pass);
    }

    bool TaintAnalysis::beginFn(Function &fn) {
        if(fn.hasName()) {
           std::cout << fn.getName().str() << std::endl;
        }
        curSummary = store->getSummary(fn);
        return false;
    }

    bool TaintAnalysis::transfer(Instruction &ins) {
        //ins.print(outs(), true);
        return curSummary->propagate(ins);
    }

    bool TaintAnalysis::endFn(Function &fn) {
        string fnName = fn.getName().str();
        bool changed = curSummary->didSummaryChange();
        curSummary->getAliasWrapper().invalidate();
        curSummary = nullptr;
        return changed;
    }
}