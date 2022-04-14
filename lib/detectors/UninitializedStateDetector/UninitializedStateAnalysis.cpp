//
// Created by Jon Stephens on 3/20/22.
//

#include "UninitializedStateAnalysis.h"
#include <iostream>
#include "llvm/IR/Instructions.h"
#include <string>

using namespace std;
using namespace blockchain;

namespace UninitializedState {
    UninitializedStateAnalysis::UninitializedStateAnalysis(const blockchain::Blockchain *in_chain) : Analysis() {
        chain = in_chain;
    }

    bool UninitializedStateAnalysis::shouldAnalyze(Function &fn) {
        return chain->isContractFunction(fn);
    }

    bool UninitializedStateAnalysis::beginFn(Function &fn) {
        curFn = chain->findFunction(fn);
        localInitializedVars.clear();
        return false;
    }

    bool UninitializedStateAnalysis::transfer(Instruction &ins) {
        bool modified = false;

        if(chain->readsStorage(ins)) {
            auto var = chain->readStorageVariable(ins);
            if(initializedVars.find(var) == initializedVars.end() && localInitializedVars.find(var) == localInitializedVars.end()) {
                uninitializedAccesses[curFn].insert(var);
            }
        }

        if(chain->writesStorage(ins)) {
            auto var = chain->writesStorageVariable(ins);

            if(curFn->isConstructor()) {
                if(initializedVars.insert(var).second) {
                    modified = true;
                    uninitializedAccesses.clear();
                }
            }
            else {
                localInitializedVars.insert(var);
            }
        }

        /*if (auto CallInstr = dyn_cast<CallInst>(&ins)) {
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

        }*/
        return modified;
    }

    bool UninitializedStateAnalysis::endFn(Function &fn) {
        return false;
    }

    string UninitializedStateAnalysis::vulnerabilityReport()  {
        string report = "Uninitialized State Report:\n";
        for(auto p : uninitializedAccesses) {
            string funcname = p.first->name();
            auto vnames = p.second;
            for(auto vname : vnames) {
                report += "Function '" + funcname + "' has potential access to uninitialized state variable '" + vname->name() + "' !\n";
            }
        }
        report += "--------\nDone!";
        return report;
    }
}