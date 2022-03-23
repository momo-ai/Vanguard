//
// Created by Jon Stephens on 3/20/22.
//

#ifndef VANGUARD_MODPRINT_H
#define VANGUARD_MODPRINT_H

#include "../../Analysis.h"

using namespace vanguard;

namespace Reentrancy {
    class ReentrancyAnalysis : public Analysis {
    public:
        bool shouldAnalyze(const Function &fn) override;
        bool beginFn(const Function &fn) override;
        bool transfer(const Instruction &ins) override;
        bool endFn(const Function &fn) override;
        string vulnerabilityReport() override;
    private:
        const Function *currFn; // Tracks current function being analyzed
        const Function *lastExternalCall = NULL; // Tracks last external call
//        vector<tuple<int*,int*>> potentialReentrancies; // Tracks potential reentrant funcs and external call
        vector<tuple<string,string>> potentialReentrancies; // Tracks potential reentrant funcs and external call
        bool isExternal(const Function &fn) {
            return true;
        }
    };
}

#endif //VANGUARD_MODPRINT_H
