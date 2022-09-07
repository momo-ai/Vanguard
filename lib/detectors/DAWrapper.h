//
// Created by Kostas Ferles on 9/5/22.
//

#ifndef VANGUARD_DAWRAPPER_H
#define VANGUARD_DAWRAPPER_H

#include <map>
#include <llvm/Analysis/DependenceAnalysis.h>
#include "../program/Function.h"

namespace vanguard {
    class DAWrapper {
    public:
        DAWrapper();
        virtual llvm::DependenceInfo *request(Function &reqFn) = 0;
    protected:
        std::map<Function*, llvm::DependenceInfo*> depInfo;
    };
}


#endif //VANGUARD_DAWRAPPER_H
