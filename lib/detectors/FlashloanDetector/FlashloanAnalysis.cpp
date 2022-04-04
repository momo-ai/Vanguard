//
// Created by Jon Stephens on 3/30/22.
//

#include <iostream>
#include "FlashloanAnalysis.h"
#include "../../TaintLabel.h"
#include "../../TaintLabelStore.h"
#include "../../TaintSummary.h"
#include "llvm/IR/Function.h"
#include <sstream>

using namespace vanguard;
using namespace llvm;
using namespace std;

namespace flashloan {
    FlashloanAnalysis::FlashloanAnalysis(vector<FunctionTaintSink *> &sinks,
                                               vector<FunctionTaintSource *> &sources) : TaintAnalysis(sinks, sources) {

    }

    bool FlashloanAnalysis::shouldAnalyze(Function &fn) {
        return true;
    }

    string FlashloanAnalysis::vulnerabilityReport() {
        stringstream ss;
        ss << "Flashloan Vulnerability Report:" << endl;
        for(auto sink : sinks) {
            for(auto fn : sink->generatingFns()) {
                ss << "Function: " << fn->getName().str() << endl;
            }

        }

        ss << "--------" << endl << "Done!" << endl;
        return ss.str();
    }
}

