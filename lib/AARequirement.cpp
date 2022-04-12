//
// Created by Jon Stephens on 4/11/22.
//

#include "AARequirement.h"

using namespace blockchain;

namespace vanguard {
    AARequirement *AARequirement::instance = nullptr;

    AARequirement *AARequirement::getRequirement(llvm::Pass &pass) {
        if(instance == nullptr) {
            instance = new AARequirement(pass);
        }

        return instance;
    }

    AARequirement::AARequirement(llvm::Pass &pass) : AAWrapper(pass) {}

    void AARequirement::registerRequirement(llvm::AnalysisUsage &info) const {
        info.addRequired<llvm::AAResultsWrapperPass>();
    }
}