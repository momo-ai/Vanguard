//
// Created by Benjamin Mariano on 4/3/22.
//

#include "MsgValueLoopAnalysis.h"
#include <iostream>
#include "llvm/IR/Instructions.h"
#include <string>

using namespace std;

namespace MsgValueLoop {
    MsgValueLoopAnalysis::MsgValueLoopAnalysis(const blockchain::Blockchain *in_chain) : ReachAnalysis() {
        chain = in_chain;
        curFn = nullptr;
    }

    bool MsgValueLoopAnalysis::shouldAnalyze(Function &fn) {
        return chain->isContractFunction(fn);
    }

    bool MsgValueLoopAnalysis::beginFn(Function &fn) {
        ReachAnalysis::beginFn(fn);
        curFn = &fn;
        return false;
    }

    bool MsgValueLoopAnalysis::transfer(Instruction &ins) {
        ReachAnalysis::transfer(ins);
        bool modified = false;

        if(chain->getsValue(ins)) {
            modified = fnsWithMsgValue.insert(curFn).second || modified;
            if(Analysis::isReachable(ins, ins)) {
                modified = loopWithMsgValue.insert(curFn).second || modified;
                auto blkFn = chain->findFunction(*curFn);
                if(blkFn != nullptr && blkFn->visibility() == blockchain::PUBLIC) {
                    modified = funcsWithBadMsgValue.insert(curFn).second || modified;
                }
            }
        }

        if (auto CallInstr = dyn_cast<CallInst>(&ins)) {
            // Check for call to selfDestruct
            auto calledFn = CallInstr->getCalledFunction();
            //string cfname = called_func->getName().str();

            if(loopWithMsgValue.find(calledFn) != loopWithMsgValue.end()) {
                auto blkFn = chain->findFunction(*curFn);
                if(blkFn != nullptr && blkFn->visibility() == blockchain::PUBLIC) {
                    modified = funcsWithBadMsgValue.insert(curFn).second || modified;
                }
            }
            else if(fnsWithMsgValue.find(calledFn) != fnsWithMsgValue.end() && Analysis::isReachable(ins, ins)) {
                modified = loopWithMsgValue.insert(curFn).second || modified;
                auto blkFn = chain->findFunction(*curFn);
                if(blkFn != nullptr && blkFn->visibility() == blockchain::PUBLIC) {
                    modified = funcsWithBadMsgValue.insert(curFn).second || modified;
                }
            }
        }





        /*if (auto CallInstr = dyn_cast<CallInst>(&ins)) {
            // Check for call to selfDestruct
            Function *called_func = CallInstr->getCalledFunction();
            string cfname = called_func->getName().str();

            // TODO: Move to libBlockchain
            if (fname.find("__for_loop_body") != string::npos) {
                // Look for msg.value call in loop body
                if (chain->getsValue(ins) &&
                    count(loopWithMsgValue.begin(), loopWithMsgValue.end(), fname) == 0) {
                    // Detect call to retrieve msg.value
                    loopWithMsgValue.insert(fname);
                    modified = true;
                }
            } else {
                // Look for call to loop body
                // TODO: Move to libBlockchain
                if (cfname.find("__for_loop_body") != string::npos &&
                    count(loopWithMsgValue.begin(), loopWithMsgValue.end(), cfname) == 1) {
                    funcsWithBadMsgValue.insert(fname);
                }
            }
        }*/
        return modified;
    }

    bool MsgValueLoopAnalysis::endFn(Function &fn) {
        return false;
    }

    string MsgValueLoopAnalysis::vulnerabilityReport()  {
        string report = "mgs.value in Loop Report:\n";
        for(auto fn : funcsWithBadMsgValue) {
            for(auto pubFn : reachingPublicFns(chain, fn)) {
                report += "Function '" + pubFn->name() + "' has access to msg.value in loop!\n";
            }
        }
        report += "--------\nDone!";
        return report;
    }
}