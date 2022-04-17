//
// Created by Jon Stephens on 4/15/22.
//

#include "CGRequirement.h"
#include "llvm/Analysis/CallGraph.h"


namespace vanguard {
    CGRequirement *CGRequirement::instance = nullptr;

    CGRequirement *CGRequirement::getRequirement(llvm::Pass &pass) {
        if(instance == nullptr) {
            instance = new CGRequirement(pass);
        }

        return instance;
    }

    CGRequirement::CGRequirement(llvm::Pass &pass) : pass(pass) {}

    void CGRequirement::registerRequirement(llvm::AnalysisUsage &info) const {
        info.addRequired<llvm::CallGraphWrapperPass>();
    }

    llvm::CallGraph &CGRequirement::getCallGraph() {
        auto &cg = pass.getAnalysis<llvm::CallGraphWrapperPass>().getCallGraph();
        return cg;
    }
}