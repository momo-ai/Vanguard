//
// Created by Benjamin Mariano on 4/3/22.
//

#include "DelegatecallLoopAnalysis.h"
#include <iostream>
#include "llvm/IR/Instructions.h"
#include <string>

using namespace std;

namespace DelegatecallLoop {
    DelegatecallLoopAnalysis::DelegatecallLoopAnalysis(const blockchain::Blockchain *in_chain) : Analysis() {
        chain = in_chain;
    }

    bool DelegatecallLoopAnalysis::shouldAnalyze(Function &fn) {
        return chain->isContractFunction(fn);
    }

    bool DelegatecallLoopAnalysis::beginFn(Function &fn) {
        fname = fn.getName().str();
        isPayable = chain->findFunction(fn)->mutability() == blockchain::Mutability::PAYABLE;
        return false;
    }

    bool DelegatecallLoopAnalysis::transfer(Instruction &ins) {
        bool modified = false;
        if (auto CallInstr = dyn_cast<CallInst>(&ins)) {
            // Check for call to selfDestruct
            Function *called_func = CallInstr->getCalledFunction();
            string cfname = called_func->getName().str();

            // TODO: Move to libBlockchain
            if (fname.find("__for_loop_body") != string::npos) {
                // Look for delegate call in loop body
                if (cfname.compare("callDelegate") == 0 &&
                    count(loopWithDelegate.begin(), loopWithDelegate.end(), fname) == 0) {
                    // Detect call to retrieve msg.value
                    loopWithDelegate.insert(fname);
                    modified = true;
                }
            } else {
                // Look for call to loop body
                // TODO: Move to libBlockchain
                if (cfname.find("__for_loop_body") != string::npos &&
                    count(loopWithDelegate.begin(), loopWithDelegate.end(), cfname) == 1 &&
                    isPayable) {
                    funcsWithBadDelegate.insert(fname);
                }
            }
        }
        return modified;
    }

    bool DelegatecallLoopAnalysis::endFn(Function &fn) {
        return false;
    }

    string DelegatecallLoopAnalysis::vulnerabilityReport()  {
        string report = "delegatecall in payable Loop Report:\n";
        for(string funcname : funcsWithBadDelegate) {
            report += "Function '" + funcname + "' has call to delegatecall in payable loop!\n";
        }
        report += "--------\nDone!";
        return report;
    }
}
