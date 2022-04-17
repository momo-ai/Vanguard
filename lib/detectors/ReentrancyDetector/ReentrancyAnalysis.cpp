//
// Created by Jon Stephens on 3/20/22.
//

#include "ReentrancyAnalysis.h"
#include <iostream>
#include "llvm/IR/Instructions.h"

using namespace std;

namespace Reentrancy {
    ReentrancyAnalysis::ReentrancyAnalysis(const blockchain::Blockchain *in_chain) : ReachAnalysis() {
        chain = in_chain;
    }

    bool ReentrancyAnalysis::shouldAnalyze(Function &fn) {
        return chain->isContractFunction(fn);
    }

    bool ReentrancyAnalysis::beginFn(Function &fn) {
        ReachAnalysis::beginFn(fn);
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

    bool ReentrancyAnalysis::transfer(Instruction &ins) {
        ReachAnalysis::transfer(ins);
        if (auto CallInstr = dyn_cast<CallInst>(&ins)) {
            // Detect function call
            Function *calledFn = CallInstr->getCalledFunction();
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
            if (chain->isAnyExternalCall(*calledFn)) { // && !chain->callHasKeccik(*called_func)) {
                auto arg = CallInstr->getArgOperand(1);
                if (auto i1 = dyn_cast<Instruction>(arg)) {
                    // If call is external, record that current func has ext and set last ext call
                    lastExternalCall = calledFn;
                    if (!get<0>(fnInfo[curFn])) {
                        // Indicate function has ext call if not already indicated
                        fnInfo[curFn] = make_tuple(true, get<1>(fnInfo[curFn]));
                        modified = true;
                    }
                }
            }
        }

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

    bool ReentrancyAnalysis::endFn(Function &fn) {
        return modified;
    }

    string ReentrancyAnalysis::vulnerabilityReport()  {
        string report = "Reentrancy Report:\n";
        for(pair<Function *, Function *> tup : potentialReentrancies) {
            for(auto pubFn : reachingPublicFns(chain, tup.first)) {
                report += "Function '" + chain->findFunction(*tup.first)->name() + "' has potential reentrancy \n";
            }

            /*if(chain->isContractFunction(*tup.first)) {
                report += "Function '" + chain->findFunction(*tup.first)->name() + "' has potential reentrancy \n"; //after call to '" + get<1>(tup) + "'\n";
            }
            else {
                report += "Function '" + get<0>(tup)->getName().str() + "' has potential reentrancy \n";//after call to '" + get<1>(tup) + "'\n";
            }*/


        }
        report += "--------\nDone!";
        return report;
    }
}