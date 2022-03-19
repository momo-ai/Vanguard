//
// Created by Jon Stephens on 3/18/22.
//

#ifndef VANGUARD_ANALYSIS_H
#define VANGUARD_ANALYSIS_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"

using namespace std;
using namespace llvm;

namespace vanguard {
    class Analysis {
    public:
        virtual void init() = 0;
        virtual bool shouldAnalyze(Function &fn) = 0;
        virtual bool transfer(Instruction &ins) = 0;
        virtual bool isVulnerable() = 0;
        virtual string getVulnerability() = 0;
    };
}



#endif //VANGUARD_ANALYSIS_H
