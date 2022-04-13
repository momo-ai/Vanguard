//
// Created by Jon Stephens on 4/13/22.
//

#include "Analysis.h"
#include <unordered_set>
#include <list>
#include "llvm/IR/CFG.h"

namespace vanguard {
    bool Analysis::isReachable(const Instruction &from, const Instruction &to) const {
        return isReachable(*from.getParent(), *to.getParent());
    }

    bool Analysis::isReachable(const BasicBlock &from, const BasicBlock &to) const {
        list<const BasicBlock *> worklist;
        unordered_set<const BasicBlock *> seen;

        worklist.push_back(&from);
        while(!worklist.empty()) {
            auto curBlk = worklist.front();
            worklist.pop_front();

            for(auto succBlk : successors(curBlk)) {
                if(seen.find(succBlk) == seen.end()) {
                    if(succBlk == &to) {
                        return true;
                    }

                    seen.insert(succBlk);
                    worklist.push_back(succBlk);
                }
            }
        }

        return false;
    }

    /*vector<BasicBlock *> *Vanguard::reachableBlks(BasicBlock &blk, unordered_set<BasicBlock *> *exclude) {
        auto reachable = new vector<BasicBlock *>();
        list<BasicBlock *> wl;
        unordered_set<BasicBlock *> seen;

        wl.push_back(&blk);
        while(!wl.empty()) {
            BasicBlock *curBlk = wl.front();
            wl.pop_front();

            for(BasicBlock *succBlk : successors(curBlk)) {
                if(seen.find(succBlk) == seen.end()) {
                    seen.insert(succBlk);
                    wl.push_back(succBlk);
                    if(exclude == nullptr || exclude->find(succBlk) == exclude->end()) {
                        reachable->push_back(succBlk);
                    }
                }
            }
        }

        return reachable;
    }*/
}