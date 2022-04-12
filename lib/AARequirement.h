//
// Created by Jon Stephens on 4/11/22.
//

#ifndef VANGUARD_AAREQUIREMENT_H
#define VANGUARD_AAREQUIREMENT_H


#include "Requirement.h"
#include <AAWrapper.h>

namespace vanguard {
    class AARequirement : public Requirement, public blockchain::AAWrapper {
    public:
        static AARequirement *getRequirement(llvm::Pass &pass);
        void registerRequirement(llvm::AnalysisUsage &info) const override;
    private:
        static AARequirement *instance;
        explicit AARequirement(llvm::Pass &pass);
    };
}



#endif //VANGUARD_AAREQUIREMENT_H
