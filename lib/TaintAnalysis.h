//
// Created by Jon Stephens on 3/18/22.
//

#ifndef VANGUARD_TAINTANALYSIS_H
#define VANGUARD_TAINTANALYSIS_H
#include "Analysis.h"
#include "llvm/IR/Function.h"
#include "Taint.h"

//Taint analysis should be agnostic what we're running on (i.e. intraprocedural / functional)

namespace vanguard {
    class TaintAnalysis : public Analysis {
    public:
        virtual void init() override;
        /*virtual bool shouldAnalyze(Function &fn) override;
        virtual bool transfer(Instruction &ins) override;
        virtual bool isVulnerable() override;*/

        //how should we add taint source / sink?
    };
}



#endif //VANGUARD_TAINTANALYSIS_H
