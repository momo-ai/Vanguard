//
// Created by Jon Stephens on 3/30/22.
//

#include <iostream>
#include "FlashloanAnalysis.h"
#include "../../TaintLabel.h"
#include "../../TaintLabelStore.h"
#include "../../TaintSummary.h"
#include "llvm/IR/Function.h"
#include <Blockchain.h>
#include <sstream>

using namespace blockchain;
using namespace vanguard;
using namespace llvm;
using namespace std;

namespace flashloan {
    FlashloanAnalysis::FlashloanAnalysis(blockchain::AAWrapper &aa, const Blockchain *blockchain, vector<FunctionTaintSink *> &sinks,
                                               vector<FunctionTaintSource *> &sources) : blockchain(blockchain), TaintAnalysis(aa, sinks, sources) {

    }

    bool FlashloanAnalysis::shouldAnalyze(Function &fn) {
        return true;
    }

    string FlashloanAnalysis::vulnerabilityReport() {
        stringstream ss;
        ss << "Flashloan Vulnerability Report:" << endl;
        for(auto sink : sinks) {
            for(auto fn : sink->generatingFns()) {
                for(auto pubFn : reachingPublicFns(blockchain, fn)) {
                    ss << "Function '" << pubFn->name() << "' may be vulnerable to a flashloan attack" << endl;
                }

            }
        }

        ss << "--------" << endl << "Done!" << endl;
        return ss.str();
    }
}

