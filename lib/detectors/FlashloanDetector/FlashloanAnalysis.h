//
// Created by Jon Stephens on 3/30/22.
//

#ifndef VANGUARD_ANALYSISEXAMPLE_H
#define VANGUARD_ANALYSISEXAMPLE_H

#include "../../TaintAnalysis.h"
namespace flashloan {
    class FlashloanAnalysis : public vanguard::TaintAnalysis {
    public:
        FlashloanAnalysis(vector<vanguard::FunctionTaintSink *> &sinks,
                        vector<vanguard::FunctionTaintSource *> &sources);

        bool shouldAnalyze(Function &fn) override;
        string vulnerabilityReport() override;
    };
}



#endif //VANGUARD_ANALYSISEXAMPLE_H
