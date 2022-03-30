//
// Created by Jon Stephens on 3/30/22.
//

#include <iostream>
#include "AnalysisExample.h"


namespace vanguard {
    AnalysisExample::AnalysisExample(vector<FunctionTaintSink *> &sinks,
                                               vector<FunctionTaintSource *> &sources) : TaintAnalysis(sinks, sources), sinks(sinks), sources(sources) {

    }

    bool AnalysisExample::shouldAnalyze(const Function &fn) {
        return true;
    }

    string AnalysisExample::vulnerabilityReport() {
        for(auto sink : sinks) {
            auto reachingSources = sink->sources();

            if(reachingSources.empty()) {
                std::cout << "No sources reached sink" << std::endl;
            }
            else {
                std::cout << "Source reached sink" << std::endl;
            }
        }

        return "Idk Yet";
    }
}

