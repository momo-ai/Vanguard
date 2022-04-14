//
// Created by Jon Stephens on 3/20/22.
//

#include "ReentrancyAnalysis.h"
#include <iostream>
#include "llvm/IR/Instructions.h"

using namespace std;

namespace Reentrancy {
    ReentrancyAnalysis::ReentrancyAnalysis(const blockchain::Blockchain *in_chain) : Analysis() {
        chain = in_chain;
    }

    bool ReentrancyAnalysis::shouldAnalyze(Function &fn) {
        return chain->isContractFunction(fn);
    }

    bool ReentrancyAnalysis::beginFn(Function &fn) {
        fname = fn.getName().str();
        modified = false;
        lastExternalCall = NULL;
        if (fnInfo.find(fname) == fnInfo.end()) {
            // Initialize entry for function if not yet analyzed
            fnInfo[fname] = make_tuple(false, false);
        }
        return false;
    }

    bool ReentrancyAnalysis::transfer(Instruction &ins) {
        if (auto CallInstr = dyn_cast<CallInst>(&ins)) {
            // Detect function call
            Function *called_func = CallInstr->getCalledFunction();
            string cfname = called_func->getName().str();
            if (fnInfo.find(cfname) != fnInfo.end()) {
                // Run checks if called function is already analyzed
                tuple<bool,bool> calledFnInfo = fnInfo[cfname];
                if (get<1>(fnInfo[cfname])) {
                    // If call has store, record in curr func and check for prev external call
                    if (!get<1>(fnInfo[fname])) {
                        // If call has store, record that current function has store
                        fnInfo[fname] = make_tuple(get<0>(fnInfo[fname]), true);
                        modified = true;
                    }
                    if (lastExternalCall && potentialReentrancies.find(fname) == potentialReentrancies.end()) {
                        // Record reentrancy if there is prev ext call in this func (and not already recorded)
                        potentialReentrancies[fname] = lastExternalCall->getName().str();
                    }
                }
                if (get<0>(fnInfo[cfname])) {
                    // If call has external, record that current function has external call
                    lastExternalCall = called_func;
                    if (!get<0>(fnInfo[fname])) {
                        fnInfo[fname] = make_tuple(true, get<1>(fnInfo[fname]));
                        modified = true;
                    }
                }
            }
            if (chain->isAnyExternalCall(*called_func)) { // && !chain->callHasKeccik(*called_func)) {
                auto arg = CallInstr->getArgOperand(1);
                if (auto i1 = dyn_cast<Instruction>(arg)) {
                    // If call is external, record that current func has ext and set last ext call
                    lastExternalCall = called_func;
                    if (!get<0>(fnInfo[fname])) {
                        // Indicate function has ext call if not already indicated
                        fnInfo[fname] = make_tuple(true, get<1>(fnInfo[fname]));
                        modified = true;
                    }
                }
            }
        }

        if (chain->writesStorage(ins)) {
            // Detect store to contract state
            if (!get<1>(fnInfo[fname])) {
                // Indicate function has store if not already indicated
                fnInfo[fname] = make_tuple(get<0>(fnInfo[fname]), true);
                modified = true;
            }
            if (lastExternalCall && potentialReentrancies.find(fname) == potentialReentrancies.end()) {
                // Record reentrancy if there is prev ext call in this func (and not already recorded)
                potentialReentrancies[fname] = lastExternalCall->getName().str();
            }
        }
        return false;
    }

    bool ReentrancyAnalysis::endFn(Function &fn) {
        return modified;
    }

    string ReentrancyAnalysis::vulnerabilityReport()  {
        string report = "Reentrancy Report:\n";
        for(pair<string,string> tup : potentialReentrancies) {
            report += "Function '" + get<0>(tup) + "' has potential reentrancy after call to '" + get<1>(tup) + "'\n";
        }
        report += "--------\nDone!";
        return report;
    }
}