//
// Created by Jon Stephens on 3/18/22.
//

#include "TaintAnalysis.h"

namespace vanguard {

    TaintAnalysis::TaintAnalysis(std::vector<FunctionTaintSink *> &sinks, std::vector<FunctionTaintSource *> &sources) : store(sinks, sources) {

    }

    bool TaintAnalysis::beginFn(const Function &fn) {
        curSummary = store.getSummary(fn);
        return false;
    }

    bool TaintAnalysis::transfer(const Instruction &ins) {
       return curSummary->propagate(ins);
    }

    bool TaintAnalysis::endFn(const Function &fn) {
        curSummary = nullptr;
        return false;
    }
}