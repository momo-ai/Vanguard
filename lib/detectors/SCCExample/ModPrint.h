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
        bool shouldAnalyze(const Function &fn) override;
        bool beginFn(const Function &fn) override;
        bool transfer(const Instruction &ins) override;
        bool endFn(const Function &fn) override;
        string vulnerabilityReport() override;
    };
}

#endif //VANGUARD_MODPRINT_H
