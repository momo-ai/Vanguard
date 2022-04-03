//
// Created by Jon Stephens on 3/20/22.
//

#include "UninitializedStateAnalysis.h"
#include <iostream>
#include "llvm/IR/Instructions.h"
#include <string>

using namespace std;

namespace UninitializedState {
    UninitializedStateAnalysis::UninitializedStateAnalysis(const blockchain::Blockchain *in_chain) : Analysis() {
        chain = in_chain;
    }

    bool UninitializedStateAnalysis::shouldAnalyze(Function &fn) {
        return chain->isContractFunction(fn);
    }

    bool UninitializedStateAnalysis::beginFn(Function &fn) {
        fname = fn.getName().str();
        localInitializedVars.clear();
        return false;
    }

    bool UninitializedStateAnalysis::transfer(Instruction &ins) {
        bool modified = false;
        if (auto CallInstr = dyn_cast<CallInst>(&ins)) {
            // Check for call to selfDestruct
            Function *called_func = CallInstr->getCalledFunction();
            string cfname = called_func->getName().str();

            // TODO: Move to libBlockchain
            if (cfname.find("__set") != string::npos) {
                int begin = cfname.rfind("__set")+6;
                string vname = cfname.substr(begin, cfname.rfind("__")-begin);
                if (fname.find("constructor") != string::npos) {
                    // If setter found in constructor, add any initialized variable to initialized set
                    if (!visited_constructor) {
                        visited_constructor = true;
                        modified = true;
                        uninitializedAccesses.clear();
                    }
                    initializedVars.insert(vname);
                } else {
                    // If setter found in non-constructor, add to local initialized set
                    localInitializedVars.insert(vname);
                }
            } else if (cfname.find("__get") != string::npos) {
                string vname = cfname.substr(cfname.rfind("__get")+6, cfname.size()-1);
                if (count(initializedVars.begin(), initializedVars.end(), vname)+
                    count(localInitializedVars.begin(),localInitializedVars.end(), vname) == 0) {
                    uninitializedAccesses[fname].insert(vname);
                }
            }

        }
        return modified;
    }

    bool UninitializedStateAnalysis::endFn(Function &fn) {
        return false;
    }

    string UninitializedStateAnalysis::vulnerabilityReport()  {
        string report = "Uninitialized State Report:\n";
        for(pair<string,unordered_set<string>> p : uninitializedAccesses) {
            string funcname = get<0>(p);
            unordered_set<string> vnames = get<1>(p);
            for(string vname : vnames) {
                report += "Function '" + funcname + "' has potential access to uninitialized state variable '" + vname + "' !\n";
            }
        }
        report += "--------\nDone!";
        return report;
    }
}