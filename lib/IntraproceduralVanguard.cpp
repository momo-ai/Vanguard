//
// Created by Jon Stephens on 3/19/22.
//

#include "IntraproceduralVanguard.h"

#include <vector>
#include <list>
#include <iostream>

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/CFG.h"

using namespace llvm;

namespace vanguard {
    void IntraproceduralVanguard::getAnalysisUsage(llvm::AnalysisUsage &info) const {
        analysis->registerRequirements(info);
    }

    bool IntraproceduralVanguard::runOnModule(Module &m) {
        analysis->startAnalysis(*this);

        unordered_set<Function *> fnWorklist;
        vector<Function *> fns(m.getFunctionList().size());
        for(Function &f : m) {
            fns.push_back(&f);
            fnWorklist.insert(&f);
        }

        while(!fnWorklist.empty()) {
            Function *curFn = *fnWorklist.begin();
            fnWorklist.erase(fnWorklist.begin());

            bool modified = runToFixedpoint(*curFn);

            if(modified) {
                for(Function &f : m) {
                    fnWorklist.insert(&f);
                }
            }
        }

        cout << analysis->vulnerabilityReport() << endl;

        return false;
    }
}