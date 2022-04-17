//
// Created by Benjamin Mariano on 4/3/22.
//

#include "DelegatecallLoopAnalysis.h"
#include <iostream>
#include "llvm/IR/Instructions.h"
#include <string>

using namespace std;

namespace DelegatecallLoop {
    DelegatecallLoopAnalysis::DelegatecallLoopAnalysis(const blockchain::Blockchain *in_chain) : ReachAnalysis() {
        chain = in_chain;
    }

    bool DelegatecallLoopAnalysis::shouldAnalyze(Function &fn) {
        return chain->isContractFunction(fn);
    }

    bool DelegatecallLoopAnalysis::beginFn(Function &fn) {
        ReachAnalysis::beginFn(fn);
        curFn = &fn;
        isPayable = chain->findFunction(fn)->mutability() == blockchain::Mutability::PAYABLE;
        return false;
    }

    bool DelegatecallLoopAnalysis::transfer(Instruction &ins) {
        ReachAnalysis::transfer(ins);
        bool modified = false;

        if (auto CallInstr = dyn_cast<CallInst>(&ins)) {
            // Check for call to selfDestruct
            Function *calledFn = CallInstr->getCalledFunction();
            //string cfname = called_func->getName().str();

            if(chain->isDelegateCall(*calledFn)) {
                modified = fnsWithDelegateCall.insert(curFn).second || modified;
                if(Analysis::isReachable(ins, ins)) {
                    modified = loopWithDelegate.insert(curFn).second || modified;
                    if(isPayable) {
                        modified = funcsWithBadDelegate.insert(curFn).second || modified;
                    }
                }
            }
            else if(loopWithDelegate.find(calledFn) != loopWithDelegate.end()) {
                if(isPayable) {
                    funcsWithBadDelegate.insert(curFn);
                }
            }
            else if(fnsWithDelegateCall.find(calledFn) != fnsWithDelegateCall.end() && Analysis::isReachable(ins, ins)) {
                modified = loopWithDelegate.insert(curFn).second || modified;
                if(isPayable) {
                    modified = funcsWithBadDelegate.insert(curFn).second || modified;
                }
            }


            /*// TODO: Move to libBlockchain
            if (fname.find("__for_loop_body") != string::npos) {
                // Look for delegate call in loop body
                //if (cfname.compare("callDelegate") == 0 &&
                if(chain->isDelegateCall(*called_func) &&
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
            }*/
        }
        return modified;
    }

    bool DelegatecallLoopAnalysis::endFn(Function &fn) {
        return false;
    }

    string DelegatecallLoopAnalysis::vulnerabilityReport()  {
        string report = "delegatecall in payable Loop Report:\n";
        for(auto fn : funcsWithBadDelegate) {
            for(auto pubFn : reachingPublicFns(chain, fn)) {
                report += "Function '" + pubFn->name() + "' has call to delegatecall in payable loop!\n";
            }
        }
        report += "--------\nDone!";
        return report;
    }
}
