//
// Created by Ben Mariano on 4/3/22.
//

#ifndef VANGUARD_TAINTEDSENDANALYSIS_H
#define VANGUARD_TAINTEDSENDANALYSIS_H

#include "../../TaintAnalysis.h"

using namespace vanguard;
using namespace std;

namespace TaintedSend {
    class TaintedSendAnalysis : public TaintAnalysis {
    public:
        TaintedSendAnalysis(blockchain::AAWrapper &aa, vector<FunctionTaintSink *> &sinks,
                            vector<FunctionTaintSource *> &sources);

        bool shouldAnalyze(Function &fn) override;
        string vulnerabilityReport() override;
    private:
        vector<FunctionTaintSink *> sinks;
        vector<FunctionTaintSource *> sources;
    };
}



#endif //VANGUARD_TAINTEDSENDANALYSIS_H
