//
// Created by Jon Stephens on 3/30/22.
//

#include "TaintExample.h"
#include "AnalysisExample.h"
#include "ExampleSource.h"
#include "ExampleSink.h"
#include <vector>

namespace vanguard {
    TaintExample::TaintExample() : IntraproceduralVanguard(ID) {
        ExampleSource *src = new ExampleSource();
        ExampleSink *sink = new ExampleSink();
        std::vector<FunctionTaintSource *> sources = {src};
        std::vector<FunctionTaintSink *> sinks = {sink};
        analysis = new AnalysisExample(sinks, sources);
        Vanguard::registerAnalysis(analysis);
    }

    char TaintExample::ID = 0;
    static RegisterPass<TaintExample> X("taint-example", "Taint Analysis Example",
                                                  true /* Only looks at CFG */,
                                                  true /* Analysis Pass */);
}