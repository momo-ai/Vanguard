//
// Created by Jon Stephens on 3/30/22.
//

#ifndef VANGUARD_ANALYSISEXAMPLE_H
#define VANGUARD_ANALYSISEXAMPLE_H

#include "../../TaintAnalysis.h"
namespace vanguard {
    class AnalysisExample : public TaintAnalysis {
    public:
        AnalysisExample(vector<FunctionTaintSink *> &sinks,
                        vector<FunctionTaintSource *> &sources);

        bool shouldAnalyze(Function &fn) override;
        string vulnerabilityReport() override;
    private:
        vector<FunctionTaintSink *> sinks;
        vector<FunctionTaintSource *> sources;
    };
}



#endif //VANGUARD_ANALYSISEXAMPLE_H
