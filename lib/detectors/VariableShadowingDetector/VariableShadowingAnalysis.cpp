//
// Created by Jon Stephens on 4/4/22.
//

#include "VariableShadowingAnalysis.h"
#include <BlkContract.h>
#include <algorithm>
#include <sstream>

using namespace blockchain;
using namespace llvm;
using namespace vanguard;
using namespace std;

namespace shadowing {

    VariableShadowingAnalysis::VariableShadowingAnalysis(const blockchain::Blockchain *blk) : blk(blk){
        for(auto contract : blk->contracts()) {
            for(auto var : contract->variables()) {
                contractToVars[contract].insert(var->name());
                varnameToVar[contract][var->name()] = var;
                varToContract[var] = contract;
            }
        }

        findShadows();
    }

    void VariableShadowingAnalysis::findShadows() {
        for(BlkContract *contract : blk->contracts()) {
            unordered_set<string> contractVars = contractToVars.at(contract);
            for(BlkContract *inherit : contract->inherits()) {
                unordered_set<string> inheritVars = contractToVars.at(inherit);
                vector<string> intersect;
                set_intersection(contractVars.begin(), contractVars.end(), inheritVars.begin(), inheritVars.end(), intersect.begin());
                for(string varName : intersect) {
                    shadows[varnameToVar[contract][varName]] = varnameToVar[inherit][varName];
                }
            }
        }
    }

    bool VariableShadowingAnalysis::shouldAnalyze(Function &fn) {
        return blk->isContractFunction(fn);
    }

    /*
     * Eventually look for accesses to shadowing and shadowed variables so that we can point out where they are used.
     */
    bool VariableShadowingAnalysis::beginFn(Function &fn) {
        return false;
    }

    bool VariableShadowingAnalysis::transfer(Instruction &ins) {
        return false;
    }

    bool VariableShadowingAnalysis::endFn(Function &fn) {
        return false;
    }

    string VariableShadowingAnalysis::vulnerabilityReport() {
        stringstream ss;

        ss << "Variable Shadowing Vulnerability Report:" << endl;
        for(auto shadow : shadows) {
            BlkVariable *var = shadow.first;
            BlkVariable *inherited = shadow.second;

            ss << varToContract[var]->name() << "." << var->name() << " shadows ";
            ss << varToContract[inherited]->name() << "." << inherited->name() << endl;
        }

        ss << "--------" << endl << "Done!" << endl;
        return ss.str();
    }
}