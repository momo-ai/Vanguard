//
// Created by Jon Stephens on 3/19/22.
//

#include "SCCVanguard.h"
#include "llvm/Analysis/CallGraph.h"
#include "Analysis.h"


namespace vanguard {
    void SCCVanguard::getAnalysisUsage(llvm::AnalysisUsage &info) const  {
        for(Requirement *req : requirements) {
            req->registerRequirement(info);
        }
    }

    bool SCCVanguard::runOnSCC(CallGraphSCC &scc) {
        if(!started) {
            analysis->startAnalysis();
            started = true;
        }

        for(auto node : scc) {
            Function *fn = node->getFunction();
            if(fn != nullptr) {
                runToFixedpoint(*fn);
            }
        }

        return false;
    }
}