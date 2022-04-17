//
// Created by Jon Stephens on 4/17/22.
//

#ifndef VANGUARD_REACHANALYSIS_H
#define VANGUARD_REACHANALYSIS_H

#include "Analysis.h"
#include <unordered_set>
#include <unordered_map>
#include <BlkFunction.h>

namespace vanguard {
    class ReachAnalysis : public Analysis {
    public:
        virtual bool beginFn(Function &fn);
        virtual bool transfer(Instruction &ins);

        /*
         * These functions are intended to be used after the analysis has been completed.
         */
        std::unordered_map<const llvm::Function *, std::unordered_set<const llvm::Function *>> reachableBy;
        bool isReachable(const Function *from, const Function *to);
        vector<const blockchain::BlkFunction *> reachingPublicFns(const blockchain::Blockchain *chain, const Function *fn);
    private:
        const llvm::Function *curFn;


    };
}



#endif //VANGUARD_REACHANALYSIS_H
