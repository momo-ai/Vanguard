//
// Created by Jon Stephens on 3/20/22.
//

#ifndef VANGUARD_MODPRINT_H
#define VANGUARD_MODPRINT_H

#include "../../Analysis.h"

using namespace vanguard;

namespace sccexample {
    class ModPrint : public Analysis {
    public:
        bool shouldAnalyze(Function &fn) override;
        bool beginFn(Function &fn) override;
        bool transfer(Instruction &ins) override;
        bool endFn(Function &fn) override;
        string vulnerabilityReport() override;
    };
}

#endif //VANGUARD_MODPRINT_H
