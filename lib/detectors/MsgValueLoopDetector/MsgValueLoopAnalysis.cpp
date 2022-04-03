//
// Created by Benjamin Mariano on 4/3/22.
//

#include "MsgValueLoopAnalysis.h"
#include <iostream>
#include "llvm/IR/Instructions.h"
#include <string>

using namespace std;

namespace MsgValueLoop {
    MsgValueLoopAnalysis::MsgValueLoopAnalysis(const blockchain::Blockchain *in_chain) : Analysis() {
        chain = in_chain;
    }

    bool MsgValueLoopAnalysis::shouldAnalyze(Function &fn) {
        return chain->isContractFunction(fn);
    }

    bool MsgValueLoopAnalysis::beginFn(Function &fn) {
        fname = fn.getName().str();
        return false;
    }

    bool MsgValueLoopAnalysis::transfer(Instruction &ins) {
        bool modified = false;
        if (auto CallInstr = dyn_cast<CallInst>(&ins)) {
            // Check for call to selfDestruct
            Function *called_func = CallInstr->getCalledFunction();
            string cfname = called_func->getName().str();

            // TODO: Move to libBlockchain
            if (fname.find("__for_loop_body") != string::npos) {
                // Look for msg.value call in loop body
                if (cfname.compare("getCallValue") == 0 &&
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
        }
        return modified;
    }

    bool MsgValueLoopAnalysis::endFn(Function &fn) {
        return false;
    }

    string MsgValueLoopAnalysis::vulnerabilityReport()  {
        string report = "mgs.value in Loop Report:\n";
        for(string funcname : funcsWithBadMsgValue) {
            report += "Function '" + funcname + "' has access to msg.value in loop!\n";
        }
        report += "--------\nDone!";
        return report;
    }
}