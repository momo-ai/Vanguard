//
// Created by Jon Stephens on 3/19/22.
//

#include "Vanguard.h"
#include "llvm/Analysis/CFG.h"
#include "llvm/IR/CFG.h"
#include "llvm/Support/CommandLine.h"
#include <list>
#include <stdexcept>
#include <SummaryReader.h>

namespace vanguard {
    cl::opt<string> inputSummary("summary", cl::desc("Input Smart Contract Summary"), cl::value_desc("filename"));
    void Vanguard::registerAnalysis(Analysis *a) {
        analysis = a;
    }

    const blockchain::Blockchain *Vanguard::blockchain() {
        if(chain == nullptr) {
            if(inputSummary.empty()) {
                throw runtime_error("A summary must be provided using --summary=filename");
            }
            blockchain::SummaryReader reader(inputSummary);
            chain = reader.blockchain();
        }

        return chain;
    }

    vector<const BasicBlock *> *Vanguard::reachableBlks(const BasicBlock &blk, unordered_set<const BasicBlock *> *exclude) {
        auto reachable = new vector<const BasicBlock *>();
        list<const BasicBlock *> wl;
        unordered_set<const BasicBlock *> seen;

        wl.push_back(&blk);
        while(!wl.empty()) {
            const BasicBlock *curBlk = wl.front();
            wl.pop_front();

            for(const BasicBlock *succBlk : successors(curBlk)) {
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
    }

    bool Vanguard::runToFixedpoint(const Function &fn) {
        if(!analysis->shouldAnalyze(fn)) {
            return false;
        }

        bool modified = false;
        modified = analysis->beginFn(fn) || modified;

        unordered_set<const BasicBlock *> wlContents;
        list<const BasicBlock *> bbWorklist;
        for(const BasicBlock &bb : fn) {
            wlContents.insert(&bb);
            bbWorklist.insert(bbWorklist.end(), &bb);
        }

        while(!bbWorklist.empty()) {
            const BasicBlock *blk = bbWorklist.front();
            bbWorklist.pop_front();
            wlContents.erase(blk);

            for(const Instruction &ins : *blk) {
                if(analysis->transfer(ins)) {
                    modified = true;
                    vector<const BasicBlock *> *reachable = reachableBlks(*blk, &wlContents);
                    bbWorklist.insert(bbWorklist.begin(), reachable->begin(), reachable->end());
                    wlContents.insert(reachable->begin(), reachable->end());
                    delete reachable;
                }
            }
        }

        modified = analysis->endFn(fn) || modified;

        return modified;
    }
}