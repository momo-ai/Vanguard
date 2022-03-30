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
        ReentrancyAnalysis(const blockchain::Blockchain *in_chain);
        bool shouldAnalyze(const Function &fn) override;
        bool beginFn(const Function &fn) override;
        bool transfer(const Instruction &ins) override;
        bool endFn(const Function &fn) override;
        string vulnerabilityReport() override;
    private:
        const Function *lastExternalCall = NULL; // Tracks last external call
        string fname; // Current function name
        map<string,string> potentialReentrancies; // Tracks potential reentrant funcs and external call
        map<string,tuple<bool,bool>> fnInfo; // Tracks for each func if it (1) has extern call or (2) has store
        bool modified; // Tracks if current function being analyzed has been updated in fnInfo on this pass
        bool isExternal(const Function &fn) {
            return true;
        }
        const blockchain::Blockchain *chain;
    };
}

#endif //VANGUARD_MODPRINT_H
