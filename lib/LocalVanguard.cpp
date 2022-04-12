//
// Created by Jon Stephens on 3/19/22.
//

#include "LocalVanguard.h"


namespace vanguard {
    void LocalVanguard::getAnalysisUsage(llvm::AnalysisUsage &info) const  {
        for(Requirement *req : requirements) {
            req->registerRequirement(info);
        }
    }

    bool LocalVanguard::runOnFunction(Function &fn) {
        if(!started) {
            analysis->startAnalysis();
            started = true;
        }
        runToFixedpoint(fn);
        return false;
    }

}