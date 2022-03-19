//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_SCCVANGUARD_H
#define VANGUARD_SCCVANGUARD_H

#include "llvm/Pass.h"
#include "Vanguard.h"
#include "llvm/Analysis/CallGraphSCCPass.h"

namespace vanguard {
    class SCCVanguard : public CallGraphSCCPass, public Vanguard {
    public:
        SCCVanguard(char &ID) : CallGraphSCCPass(ID) {}
        virtual bool runOnSCC(CallGraphSCC &SCC) override;
    };
}



#endif //VANGUARD_SCCVANGUARD_H
