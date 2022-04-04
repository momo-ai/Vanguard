//
// Created by Jon Stephens on 3/20/22.
//

#include "SuicideAnalysis.h"
#include <iostream>
#include "llvm/IR/Instructions.h"

using namespace std;

namespace Suicide {
    SuicideAnalysis::SuicideAnalysis(const blockchain::Blockchain *in_chain) : Analysis() {
        chain = in_chain;
    }

    bool SuicideAnalysis::shouldAnalyze(Function &fn) {
        return chain->isContractFunction(fn);
    }

    bool SuicideAnalysis::beginFn(Function &fn) {
        fname = fn.getName().str();
        // TODO: Move to blockchain
        if (chain->findFunction(fn)->visibility() == blockchain::Visibility::PUBLIC ||
            chain->findFunction(fn)->visibility() == blockchain::Visibility::EXTERNAL ||
            chain->findFunction(fn)->visibility() == blockchain::Visibility::DEFAULT) {
//        if (true) {
            pubFuncs.insert(fname);
        }
        hasModifier = false;
        return false;
    }

    bool SuicideAnalysis::transfer(Instruction &ins) {
        bool modified = false;
        if (auto CallInstr = dyn_cast<CallInst>(&ins)) {
            // Check for call to selfDestruct
            Function *called_func = CallInstr->getCalledFunction();
            string cfname = called_func->getName().str();
            if (count(potentialSuicides.begin(), potentialSuicides.end(), cfname) &&
                !count(potentialSuicides.begin(), potentialSuicides.end(), fname)) {
                potentialSuicides.push_back(fname);
                modified = true;
            }
            // TODO: Move this to libblockchain
            if (cfname.compare("selfDestruct") == 0 &&
                !count(potentialSuicides.begin(), potentialSuicides.end(), fname)) {
                potentialSuicides.push_back(fname);
                modified = true;
            }
        }
        return modified;
    }

    bool SuicideAnalysis::endFn(Function &fn) {
        return false;
    }

    string SuicideAnalysis::vulnerabilityReport()  {
        string report = "Suicide Report:\n";
        for(string fname : potentialSuicides) {
            if (count(pubFuncs.begin(), pubFuncs.end(), fname)) {
                report += "Function '" + fname + "' has potential unprotected suicide call!\n";
            }
        }
        report += "--------\nDone!";
        return report;
    }
}