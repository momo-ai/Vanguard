//
// Created by Jon Stephens on 3/18/22.
//

#include "TaintAnalysis.h"

namespace vanguard {

    Instruction *prevIns(Instruction &ins) {
        return ins.getPrevNode();
    }

    bool TaintAnalysis::transfer(const Instruction &ins) {
       /* vector<Val> reads = rwInfo.reads(ins);
        vector<Val> writes = rwInfo.writes(ins);
        Instruction *prev = prevIns(ins);

        return test;*/
       return false;
    }

    void TaintAnalysis::registerSource(FunctionTaintSource &src) {
        fnSources.push_back(&src);
    }

    void TaintAnalysis::registerSink(FunctionTaintSink &sink) {
        fnSinks.push_back(&sink);
    }
}