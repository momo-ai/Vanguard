//
// Created by Jon Stephens on 3/18/22.
//

#ifndef VANGUARD_ANALYSIS_H
#define VANGUARD_ANALYSIS_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include <SummaryReader.h>
#include "llvm/Pass.h"

using namespace std;
using namespace llvm;

namespace vanguard {
    class Analysis {
    public:
        virtual ~Analysis() = default;
        //virtual void init() = 0;
        virtual void startAnalysis() {}
        virtual bool shouldAnalyze(Function &fn) = 0;
        virtual bool beginFn(Function &fn) = 0;
        virtual bool transfer(Instruction &ins) = 0;
        virtual bool endFn(Function &fn) = 0;
        //virtual bool isVulnerable() = 0;
        virtual string vulnerabilityReport() = 0;
        static bool isReachable(const Instruction &from, const Instruction &to);
        static bool isReachable(const BasicBlock &from, const BasicBlock &to);

    protected:
    };
}



#endif //VANGUARD_ANALYSIS_H
