//
// Created by Jon Stephens on 8/13/22.
//

#ifndef VANGUARD_INTERPROCEDURALDETECTOR_H
#define VANGUARD_INTERPROCEDURALDETECTOR_H

#include <unordered_set>
#include <deque>
#include "UnitDetector.h"
#include <program/CompilationUnit.h>

namespace vanguard {
    template<class Domain>
    class FunctionDetector : public UnitDetector<Domain> {
    public:
        virtual bool detect(typename Domain::Function &fn) = 0;
        void detect(typename Domain::CompilationUnit &unit) override {
            std::unordered_set<typename Domain::Function *> processed;
            std::deque<typename Domain::Function *> fnWorklist;
            for(auto f : unit.functions()) {
                fnWorklist.push_back(dynamic_cast<typename Domain::Function *>(f));
            }

            while(!fnWorklist.empty()) {
                typename Domain::Function *curFn = fnWorklist.front();
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
