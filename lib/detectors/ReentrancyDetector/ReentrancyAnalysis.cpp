//
// Created by Jon Stephens on 3/20/22.
//

#include "ReentrancyAnalysis.h"
#include <iostream>
#include "llvm/IR/Instructions.h"

using namespace std;

namespace Reentrancy {
    bool ReentrancyAnalysis::shouldAnalyze(const Function &fn) {
        return true;
    }

    bool ReentrancyAnalysis::beginFn(const Function &fn) {
        lastExternalCall = NULL;
        currFn = &fn;
        return false;
    }

    bool ReentrancyAnalysis::transfer(const Instruction &ins) {
        if (auto CallInstr = dyn_cast<CallInst>(&ins)) {
            Function *called_func = CallInstr->getCalledFunction();
            if (isExternal(*called_func)) {
                lastExternalCall = called_func;
            }
        } else if (auto StoreInstr = dyn_cast<StoreInst>(&ins)) {
            if (lastExternalCall) {
                potentialReentrancies.push_back(make_tuple(currFn->getName().str(),lastExternalCall->getName().str()));
            }
        }
        return false;
    }

    bool ReentrancyAnalysis::endFn(const Function &fn) {
        lastExternalCall = NULL;
        return false;
    }

    string ReentrancyAnalysis::vulnerabilityReport()  {
        string report = "Reentrancy Report:\n";
        for(tuple<string,string> tup : potentialReentrancies) {
            report += "Function '" + get<0>(tup) + "' has potential reentrancy after call to '" + get<1>(tup) + "'\n";
        }
        report += "--------\nDone!";
        return report;
    }
}