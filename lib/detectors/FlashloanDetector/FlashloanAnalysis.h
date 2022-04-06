//
// Created by Jon Stephens on 3/30/22.
//

#ifndef VANGUARD_ANALYSISEXAMPLE_H
#define VANGUARD_ANALYSISEXAMPLE_H

#include "../../TaintAnalysis.h"
#include <Blockchain.h>
namespace flashloan {
    class FlashloanAnalysis : public vanguard::TaintAnalysis {
    public:
        FlashloanAnalysis(const blockchain::Blockchain *blockchain, vector<vanguard::FunctionTaintSink *> &sinks,
                        vector<vanguard::FunctionTaintSource *> &sources);

        bool shouldAnalyze(Function &fn) override;
        string vulnerabilityReport() override;
    private:
        const blockchain::Blockchain *blockchain;
    };
}



#endif //VANGUARD_ANALYSISEXAMPLE_H
