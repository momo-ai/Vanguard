//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_LOCALVANGUARD_H
#define VANGUARD_LOCALVANGUARD_H

#include "llvm/Pass.h"
#include "Analysis.h"
#include "Vanguard.h"

namespace vanguard {
    class LocalVanguard : public FunctionPass, public Vanguard {
    public:
        explicit LocalVanguard(char &ID) : FunctionPass(ID), started(false) {}
        void getAnalysisUsage(llvm::AnalysisUsage &Info) const override;
        bool runOnFunction(Function &F) override;
    private:
        bool started;
    };
}



#endif //VANGUARD_LOCALVANGUARD_H
