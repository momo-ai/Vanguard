//
// Created by Jon Stephens on 4/4/22.
//

#ifndef VANGUARD_VARIABLESHADOWINGANALYSIS_H
#define VANGUARD_VARIABLESHADOWINGANALYSIS_H

#include "../../Analysis.h"
#include <unordered_map>
#include <unordered_set>

namespace shadowing {
    class VariableShadowingAnalysis : public vanguard::Analysis {
    public:
        explicit VariableShadowingAnalysis(const blockchain::Blockchain *blk);

        bool shouldAnalyze(Function &fn) override;
        bool beginFn(Function &fn) override;
        bool transfer(Instruction &ins) override;
        bool endFn(Function &fn) override;
        string vulnerabilityReport() override;
    private:
        const blockchain::Blockchain *blk;
        unordered_map<blockchain::BlkContract *, unordered_set<string>> contractToVars;
        unordered_map<blockchain::BlkVariable *, blockchain::BlkContract *> varToContract;

        unordered_map<blockchain::BlkContract *, unordered_map<string, blockchain::BlkVariable *>> varnameToVar;
        unordered_map<blockchain::BlkVariable *, blockchain::BlkVariable *> shadows;

        void findShadows();
    };
}



#endif //VANGUARD_VARIABLESHADOWINGANALYSIS_H
