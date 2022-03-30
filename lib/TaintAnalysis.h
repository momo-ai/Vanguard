//
// Created by Jon Stephens on 3/18/22.
//

#ifndef VANGUARD_TAINTANALYSIS_H
#define VANGUARD_TAINTANALYSIS_H
#include "Analysis.h"
#include "llvm/IR/Function.h"
#include "Taint.h"
#include "ReadWriteInfo.h"
#include "FunctionTaintSource.h"
#include "FunctionTaintSink.h"

//Taint analysis should be agnostic what we're running on (i.e. intraprocedural / functional)

namespace vanguard {
    class TaintAnalysis : public Analysis {
    public:
        bool transfer(const Instruction &ins) override;
        void registerSource(FunctionTaintSource &src);
        void registerSink(FunctionTaintSink &sink);

    private:
        vector<FunctionTaintSink *> fnSinks;
        vector<FunctionTaintSource *> fnSources;
        map<Instruction *, Taint *> insToTaint;
        ReadWriteInfo rwInfo;
    };
}



#endif //VANGUARD_TAINTANALYSIS_H
