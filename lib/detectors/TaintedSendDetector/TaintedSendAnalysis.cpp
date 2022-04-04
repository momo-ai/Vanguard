//
// Created by Ben Mariano on 4/3/22.
//

#include <iostream>
#include "TaintedSendAnalysis.h"
#include "../../TaintLabel.h"
#include "../../TaintLabelStore.h"
#include "../../TaintSummary.h"
#include "llvm/IR/Function.h"
#include <sstream>

namespace TaintedSend {
    TaintedSendAnalysis::TaintedSendAnalysis(vector<FunctionTaintSink *> &sinks,
                                             vector<FunctionTaintSource *> &sources) : TaintAnalysis(sinks, sources), sinks(sinks), sources(sources) {

    }

    bool TaintedSendAnalysis::shouldAnalyze(Function &fn) {
        return true;
    }

    string TaintedSendAnalysis::vulnerabilityReport() {
        stringstream ss;
        ss << "Tainted Send Vulnerability Report:" << endl;
        for(auto sink : sinks) {
            for(auto fn : sink->generatingFns()) {
                ss << "Function: " << fn->getName().str() << endl;
            }

        }

        ss << "--------" << endl << "Done!" << endl;
        return ss.str();
    }
}

