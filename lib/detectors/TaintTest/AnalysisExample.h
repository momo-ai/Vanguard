//
// Created by Jon Stephens on 3/30/22.
//

#ifndef VANGUARD_ANALYSISEXAMPLE_H
#define VANGUARD_ANALYSISEXAMPLE_H

#include "../../TaintAnalysis.h"
namespace vanguard {
    class AnalysisExample : public TaintAnalysis {
    public:
        AnalysisExample(blockchain::AAWrapper &aa, vector<FunctionTaintSink *> &sinks,
                        vector<FunctionTaintSource *> &sources);

        bool shouldAnalyze(Function &fn) override;
        string vulnerabilityReport() override;
    };
}



#endif //VANGUARD_ANALYSISEXAMPLE_H
