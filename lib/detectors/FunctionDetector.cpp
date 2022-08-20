//
// Created by Jon Stephens on 8/13/22.
//

#include "FunctionDetector.h"

namespace vanguard {

    void FunctionDetector::detect(CompilationUnit &unit) {
        std::unordered_set<Function *> processed;
        std::list<Function *> fnWorklist;
        for(auto f : unit.getAllFunctions()) {
            fnWorklist.push_back(f);
        }

        while(!fnWorklist.empty()) {
            Function *curFn = fnWorklist.front();
            fnWorklist.pop_front();
            processed.insert(curFn);

            bool modified = detect(*curFn);

            if(modified) {
                for(auto *f : processed) {
                    fnWorklist.push_back(f);
                }

                processed.clear();
            }
        }
    }
}