//
// Created by Jon Stephens on 3/30/22.
//

#include <iostream>
#include "FlashloanAnalysis.h"
#include "../../TaintLabel.h"
#include "../../TaintLabelStore.h"
#include "../../TaintSummary.h"
#include "llvm/IR/Function.h"

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
        cout << "Vulnerability Report:" << endl;
        for(auto sink : sinks) {
            for(TaintNode *node : sink->gatherTaint()) {
                TaintLabel *l = static_cast<TaintLabel *>(node);
                cout << "Function: " << l->parent().parent().function().getName().str() << endl;
                auto sources = node->sources();
                if(!sources.empty()) {
                    auto v = node->origin();
                    if(isa<RegisterVal>(v)) {
                        auto rv = cast<RegisterVal>(v);
                        cout << "  " << rv->reg().getName().str() << endl;
                    }
                    else if(isa<MemoryVal>(v)) {
                        auto mv = cast<MemoryVal>(v);
                        cout << "  " << mv->ptr().getName().str() << endl;
                    }
                }
            }

            /*auto reachingSources = sink->sources();

            if(reachingSources.empty()) {
                std::cout << "No sources reached sink" << std::endl;
            }
            else {
                std::cout << "Source reached sink" << std::endl;
            }*/
        }

        return "Idk Yet";
    }
}

