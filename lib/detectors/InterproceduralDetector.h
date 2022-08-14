//
// Created by Jon Stephens on 8/13/22.
//

#ifndef VANGUARD_INTERPROCEDURALDETECTOR_H
#define VANGUARD_INTERPROCEDURALDETECTOR_H

#include <unordered_set>
#include "UnitDetector.h"

namespace vanguard {
    template <typename Detect> class InterproceduralDetector : public UnitDetector<Detect> {
        virtual bool detect(Function &fn) = 0;

        void detect(CompilationUnit &unit) override {
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
    };
}



#endif //VANGUARD_INTERPROCEDURALDETECTOR_H
