//
// Created by Jon Stephens on 3/19/22.
//

#include "LocalVanguard.h"


namespace vanguard {
    void LocalVanguard::getAnalysisUsage(llvm::AnalysisUsage &info) const {
        analysis->registerRequirements(info);
    }

    bool LocalVanguard::runOnFunction(Function &fn) {
        if(!started) {
            analysis->startAnalysis(*this);
            started = true;
        }
        runToFixedpoint(fn);
        return false;
    }

}