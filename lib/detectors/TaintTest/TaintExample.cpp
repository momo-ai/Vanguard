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
        auto src = new ExampleSource();
        auto src2 = new ExampleSource();
        auto sink = new ExampleSink();
        std::vector<FunctionTaintSource *> sources = {src, src2};
        std::vector<FunctionTaintSink *> sinks = {sink};
        AARequirement *aliasReq = AARequirement::getRequirement(*this);
        registerRequirement(aliasReq);
        auto analysis = new AnalysisExample(*aliasReq, sinks, sources);
        Vanguard::registerAnalysis(analysis);
    }

    char TaintExample::ID = 0;
    static RegisterPass<TaintExample> X("taint-example", "Taint Analysis Example",
                                        true /* Only looks at CFG */,
                                        true /* Analysis Pass */);
}