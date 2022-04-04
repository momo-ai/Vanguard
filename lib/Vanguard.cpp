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

    Vanguard::~Vanguard() {
        delete analysis;
    }

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

    vector<BasicBlock *> *Vanguard::reachableBlks(BasicBlock &blk, unordered_set<BasicBlock *> *exclude) {
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
    }

    bool Vanguard::runToFixedpoint(Function &fn) {
        if(!analysis->shouldAnalyze(fn)) {
            return false;
        }

        bool modified = false;
        modified = analysis->beginFn(fn) || modified;

        unordered_set<BasicBlock *> wlContents;
        list<BasicBlock *> bbWorklist;
        for(BasicBlock &bb : fn) {
            wlContents.insert(&bb);
            bbWorklist.insert(bbWorklist.end(), &bb);
        }

        while(!bbWorklist.empty()) {
            BasicBlock *blk = bbWorklist.front();
            bbWorklist.pop_front();
            wlContents.erase(blk);

            for(Instruction &ins : *blk) {
                if(analysis->transfer(ins)) {
                    modified = true;
                    vector<BasicBlock *> *reachable = reachableBlks(*blk, &wlContents);
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