//
// Created by Jon Stephens on 3/20/22.
//

#ifndef VANGUARD_SUICIDE_H
#define VANGUARD_SUICIDE_H

#include "../../Analysis.h"

using namespace vanguard;

namespace Suicide {
    class SuicideAnalysis : public Analysis {
    public:
        SuicideAnalysis(const blockchain::Blockchain *in_chain);
        bool shouldAnalyze(Function &fn) override;
        bool beginFn(Function &fn) override;
        bool transfer(Instruction &ins) override;
        bool endFn(Function &fn) override;
        string vulnerabilityReport() override;
    private:
        bool hasModifier; // Stores whether or not current function has protecting modifier
        string fname; // Current function name
        vector<string> potentialSuicides; // Tracks function names with potential suicides
        vector<string> pubFuncs; // Tracks publicly executable functions
        const blockchain::Blockchain *chain;
    };
}

#endif //VANGUARD_SUICIDE_H
