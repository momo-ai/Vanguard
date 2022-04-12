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
    void IntraproceduralVanguard::getAnalysisUsage(llvm::AnalysisUsage &info) const  {
        for(Requirement *req : requirements) {
            req->registerRequirement(info);
        }
    }

    bool IntraproceduralVanguard::runOnModule(Module &m) {
        analysis->startAnalysis();

        unordered_set<Function *> inWorklist;
        list<Function *> fnWorklist;
        for(Function &f : m) {
            fnWorklist.push_back(&f);
            inWorklist.insert(&f);
        }

        while(!fnWorklist.empty()) {
            Function *curFn = fnWorklist.front();
            fnWorklist.pop_front();
            inWorklist.erase(curFn);

            bool modified = runToFixedpoint(*curFn);

            if(modified) {
                for(Function &f : m) {
                    if(inWorklist.find(&f) == inWorklist.end()) {
                        fnWorklist.push_back(&f);
                        inWorklist.insert(&f);
                    }
                }
            }
        }

        cout << analysis->vulnerabilityReport() << endl;

        return false;
    }
}