//
// Created by Jon Stephens on 8/13/22.
//

#include "FunctionDetector.h"
#include <deque>

namespace vanguard {

    void FunctionDetector::detect(CompilationUnit &unit) {
        std::unordered_set<Function *> processed;
        std::deque<Function *> fnWorklist;
        for(auto f : unit.functions()) {
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