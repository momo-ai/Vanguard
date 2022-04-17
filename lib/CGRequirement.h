//
// Created by Jon Stephens on 4/15/22.
//

#ifndef VANGUARD_CGREQUIREMENT_H
#define VANGUARD_CGREQUIREMENT_H

#include <llvm/Analysis/CallGraph.h>
#include "Requirement.h"


namespace vanguard {
    class CGRequirement : public Requirement {
    public:
        // can only get called functions. Not suitable if you want to go from fn to callers
        static CGRequirement *getRequirement(llvm::Pass &pass);
        void registerRequirement(llvm::AnalysisUsage &info) const override;
        llvm::CallGraph &getCallGraph();
    private:
        llvm::Pass &pass;

        static CGRequirement *instance;
        explicit CGRequirement(llvm::Pass &pass);
    };
}

#endif //VANGUARD_CGREQUIREMENT_H
