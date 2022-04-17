//
// Created by Jon Stephens on 4/17/22.
//

#include "ReachAnalysis.h"
#include "llvm/IR/Instructions.h"
#include <BlkFunction.h>
#include <iostream>

using namespace blockchain;

namespace vanguard {
    bool ReachAnalysis::beginFn(Function &fn) {
        curFn = &fn;
        reachableBy[curFn].insert(curFn);
        return false;
    }

    bool ReachAnalysis::transfer(Instruction &ins) {
        if(auto call = dyn_cast<CallInst>(&ins)) {
            reachableBy[call->getCalledFunction()].insert(reachableBy[curFn].begin(), reachableBy[curFn].end());
        }

        return false;
    }

    bool ReachAnalysis::isReachable(const Function *from, const Function *to) {
        return reachableBy[to].find(from) != reachableBy[from].end();
    }

    vector<const BlkFunction *> ReachAnalysis::reachingPublicFns(const Blockchain *chain, const Function *fn) {
        vector<const BlkFunction *> fns;

        unordered_set<const Function *> &reachableBySet = reachableBy[fn];

        for(auto fn : reachableBySet) {
            if(chain->isContractFunction(*fn)) {
                auto blkFn = chain->findFunction(*fn);
                if(blkFn->visibility() == blockchain::PUBLIC || blkFn->visibility() == blockchain::EXTERNAL) {
                    fns.push_back(blkFn);
                }
            }
        }

        return fns;
    }
}