//
// Created by Jon Stephens on 3/18/22.
//

#include <iostream>
#include "TaintAnalysis.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "AARequirement.h"

using namespace blockchain;

namespace vanguard {

    TaintAnalysis::TaintAnalysis(AAWrapper &aa, std::vector<FunctionTaintSink *> &sinks, std::vector<FunctionTaintSource *> &sources) : sinks(sinks), sources(sources), store(nullptr), alias(aa) {

    }

    TaintAnalysis::~TaintAnalysis() {
        delete store;
    }

    void TaintAnalysis::startAnalysis() {
        store = new TaintSummaryStore(sinks, sources, alias);
    }

    bool TaintAnalysis::beginFn(Function &fn) {
        ReachAnalysis::beginFn(fn);
        /*if(fn.hasName()) {
           std::cout << fn.getName().str() << std::endl;
        }*/
        curSummary = store->getSummary(fn);
        return false;
    }

    bool TaintAnalysis::transfer(Instruction &ins) {
        ReachAnalysis::transfer(ins);
        //ins.print(outs(), true);
        return curSummary->propagate(ins);
    }

    bool TaintAnalysis::endFn(Function &fn) {
        string fnName = fn.getName().str();
        bool changed = curSummary->didSummaryChange();
        curSummary = nullptr;
        return changed;
    }
}