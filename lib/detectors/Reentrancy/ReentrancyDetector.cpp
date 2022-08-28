//
// Created by Jon Stephens on 3/19/22.
//

#include "ReentrancyDetector.h"
#include "../../domain/libBlockchain/include/SummaryReader.h"
#include "../AARequirement.h"
#include "../../program/InstructionClasses.h"
#include <list>
#include <iostream>

namespace vanguard { // Reentrancy {
    ReentrancyDetector::ReentrancyDetector(const std::string& summaryFile) {
        if(summaryFile.empty()) {
            throw runtime_error("Must provide a summary to the reentrancy detector");
        }

        summary = summaryFile;
    }

    bool ReentrancyDetector::shouldAnalyze(vanguard::Function &fn) {
        return chain->isContractFunction(fn);
    }

    bool ReentrancyDetector::beginFn(Function &fn) {
//        ReachAnalysis::beginFn(fn);
        //fname = fn.getName().str();
        curFn = &fn;
        modified = false;
        lastExternalCall = nullptr;
        if (fnInfo.find(curFn) == fnInfo.end()) {
            // Initialize entry for function if not yet analyzed
            fnInfo[curFn] = make_tuple(false, false);
        }
        return false;
    }

    void ReentrancyDetector::visit(const CallExpr &CallInstr) {
        Function *calledFn = CallInstr.target();
        //string cfname = called_func->getName().str();
        if (fnInfo.find(calledFn) != fnInfo.end()) {
            // Run checks if called function is already analyzed
            tuple<bool,bool> calledFnInfo = fnInfo[calledFn];
            if (get<1>(fnInfo[calledFn])) {
                // If call has store, record in curr func and check for prev external call
                if (!get<1>(fnInfo[curFn])) {
                    // If call has store, record that current function has store
                    fnInfo[curFn] = make_tuple(get<0>(fnInfo[curFn]), true);
                    modified = true;
                }
                if (lastExternalCall && potentialReentrancies.find(curFn) == potentialReentrancies.end()) {
                    // Record reentrancy if there is prev ext call in this func (and not already recorded)
                    potentialReentrancies[curFn] = lastExternalCall;
                }
            }
            if (get<0>(fnInfo[calledFn])) {
                // If call has external, record that current function has external call
                lastExternalCall = calledFn;
                if (!get<0>(fnInfo[curFn])) {
                    fnInfo[curFn] = make_tuple(true, get<1>(fnInfo[curFn]));
                    modified = true;
                }
            }
        }
        if (chain->isAnyExternalCall(*calledFn)) {
            // If call is external, record that current func has ext and set last ext call
            lastExternalCall = calledFn;
            if (!get<0>(fnInfo[curFn])) {
                // Indicate function has ext call if not already indicated
                fnInfo[curFn] = make_tuple(true, get<1>(fnInfo[curFn]));
                modified = true;
            }
        }
    }

    bool ReentrancyDetector::transfer(Instruction &ins) {
//        ReachAnalysis::transfer(ins);
        ins.accept(*this);
        // TODO: hmm
        if (chain->writesStorage(ins)) {
            // Detect store to contract state
            if (!get<1>(fnInfo[curFn])) {
                // Indicate function has store if not already indicated
                fnInfo[curFn] = make_tuple(get<0>(fnInfo[curFn]), true);
                modified = true;
            }
            if (lastExternalCall && potentialReentrancies.find(curFn) == potentialReentrancies.end()) {
                // Record reentrancy if there is prev ext call in this func (and not already recorded)
                potentialReentrancies[curFn] = lastExternalCall;
            }
        }
        return false;
    }

    bool ReentrancyDetector::endFn(Function &fn) {
        return modified;
    }

    string ReentrancyDetector::vulnerabilityReport()  {
        string report = "Reentrancy Report:\n";
        for(pair<Function *, Function *> tup : potentialReentrancies) {
            report += "Function '" + chain->findFunction(*tup.first)->blkName() + "' has potential reentrancy \n";

//            for(auto pubFn : reachingPublicFns(chain, tup.first)) {
//                report += "Function '" + chain->findFunction(*tup.first)->name() + "' has potential reentrancy \n";
//            }
//            if(chain->isContractFunction(*tup.first)) {
//                report += "Function '" + chain->findFunction(*tup.first)->name() + "' has potential reentrancy \n"; //after call to '" + get<1>(tup) + "'\n";
//            }
//            else {
//                report += "Function '" + get<0>(tup)->getName().str() + "' has potential reentrancy \n";//after call to '" + get<1>(tup) + "'\n";
//            }


        }
        report += "--------\nDone!";
        return report;
    }


    vector<Block *> ReentrancyDetector::findReachable(Block &blk, unordered_set<Block *> *exclude) {
        vector<Block*> reachable = {};
        list<Block *> wl;
        unordered_set<Block *> seen;

        wl.push_back(&blk);
        while(!wl.empty()) {
            Block *curBlk = wl.front();
            wl.pop_front();

            for(Block *succBlk : curBlk->successors()) {
                if(seen.find(succBlk) == seen.end()) {
                    seen.insert(succBlk);
                    wl.push_back(succBlk);
                    if(exclude == nullptr || exclude->find(succBlk) == exclude->end()) {
                        reachable.push_back(succBlk);
                    }
                }
            }
        }

        return reachable;
    }


    // aa req here is a global var so initialize it above
    std::vector<Requirement *> ReentrancyDetector::registerAnalyses() {
        aa = new AARequirement();
        std::vector<Requirement *> res = {aa};
        return res;
    }

    void ReentrancyDetector::startDetection() {
        blockchain::SummaryReader sum = blockchain::SummaryReader(summary, aa);
        chain = sum.blockchain();
    }

    bool ReentrancyDetector::detect(Function &fn) {
        if (!shouldAnalyze(fn)) {
            return false;
        }

        string name = fn.name();
        modified = beginFn(fn) || modified;

        unordered_set<Block* > wlContents;
        list<Block* > instWorklist;
        // TODO: There is no way to iterate thru blocks in a fn
        // getbody and travel down the links
        for (Block* blk : fn.blocks()) {
            wlContents.insert(blk);
            instWorklist.insert(instWorklist.end(), blk);
        }

        while (!instWorklist.empty()) {
            Block* blk = instWorklist.front();
            instWorklist.pop_front();
            wlContents.erase(blk);

            // was in for loop when it was blocks
            for (Instruction* inst : blk->instructions()) {
                if (transfer(*inst)) {
                    modified = true;
                    // TODO: Implement re-analyzing affected  functions of true positives
                    vector<Block *> reachable = findReachable(*blk, &wlContents);
                    instWorklist.insert(instWorklist.begin(), reachable.begin(), reachable.end());
                    wlContents.insert(reachable.begin(), reachable.end());
//                    delete reachable;
                }
            }
        }

        modified = endFn(fn) || modified;

        return modified;

    }

    void ReentrancyDetector::report() {
        string theRep = vulnerabilityReport();
        std::cout << theRep << endl;
    }

    string ReentrancyDetector::name() {
        return "reentrancyBasic";
    }

}
