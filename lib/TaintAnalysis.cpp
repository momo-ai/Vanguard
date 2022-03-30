//
// Created by Jon Stephens on 3/18/22.
//

#include <iostream>
#include "TaintAnalysis.h"

namespace vanguard {

    TaintAnalysis::TaintAnalysis(std::vector<FunctionTaintSink *> &sinks, std::vector<FunctionTaintSource *> &sources) : store(sinks, sources) {

    }

    bool TaintAnalysis::beginFn(const Function &fn) {
        if(fn.hasName()) {
           std::cout << fn.getName().str() << std::endl;
        }
        curSummary = store.getSummary(fn);
        return false;
    }

    bool TaintAnalysis::transfer(const Instruction &ins) {
        //ins.print(outs(), true);
        return curSummary->propagate(ins);
    }

    bool TaintAnalysis::endFn(const Function &fn) {
        bool changed = curSummary->didSummaryChange();
        curSummary = nullptr;
        return changed;
    }
}