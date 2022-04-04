//
// Created by Ben Mariano on 4/3/22.
//

#include "TaintedSendDetector.h"
#include "TaintedSendAnalysis.h"
#include "TaintedSendSource.h"
#include "TaintedSendSink.h"
#include <vector>

namespace TaintedSend {
    TaintedSendDetector::TaintedSendDetector() : IntraproceduralVanguard(ID) {
        TaintedSendSource *src = new TaintedSendSource();
        TaintedSendSink *sink = new TaintedSendSink();
        std::vector<FunctionTaintSource *> sources = {src};
        std::vector<FunctionTaintSink *> sinks = {sink};
        analysis = new TaintedSendAnalysis(sinks, sources);
        Vanguard::registerAnalysis(analysis);
    }

    char TaintedSendDetector::ID = 0;
  static RegisterPass<TaintedSendDetector> X("tainted_send", "Detect sends tainted by user source",
                                        true /* Only looks at CFG */,
                                        true /* Analysis Pass */);
}
