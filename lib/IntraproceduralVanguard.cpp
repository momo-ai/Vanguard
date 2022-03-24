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
    bool IntraproceduralVanguard::runOnModule(Module &m) {
        unordered_set<const Function *> fnWorklist;
        vector<const Function *> fns(m.getFunctionList().size());
        for(const Function &f : m) {
            fns.push_back(&f);
            fnWorklist.insert(&f);
        }

        while(!fnWorklist.empty()) {
            const Function *curFn = *fnWorklist.begin();
            fnWorklist.erase(fnWorklist.begin());

            bool modified = runToFixedpoint(*curFn);

            if(modified) {
                for(const Function &f : m) {
                    fnWorklist.insert(&f);
                }
            }
        }

        cout << analysis->vulnerabilityReport() << endl;

        return false;
    }
}