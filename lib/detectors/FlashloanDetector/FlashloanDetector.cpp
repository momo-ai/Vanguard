//
// Created by Jon Stephens on 3/30/22.
//

#include "FlashloanDetector.h"
#include "FlashloanAnalysis.h"
#include "BalanceOfSource.h"
#include "TransferSink.h"
#include <vector>

using namespace vanguard;

namespace flashloan {
    FlashloanDetector::FlashloanDetector() : IntraproceduralVanguard(ID) {
        auto src = new BalanceOfSource();
        auto sink = new TransferSink();
        std::vector<FunctionTaintSource *> sources = {src};
        std::vector<FunctionTaintSink *> sinks = {sink};
        analysis = new FlashloanAnalysis(sinks, sources);
        Vanguard::registerAnalysis(analysis);
    }

    char FlashloanDetector::ID = 0;
    static RegisterPass<FlashloanDetector> X("flashloan", "Flashloan Detector",
                                                  true /* Only looks at CFG */,
                                                  true /* Analysis Pass */);
}