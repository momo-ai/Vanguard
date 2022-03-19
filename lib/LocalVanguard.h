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
        LocalVanguard(char &ID) : FunctionPass(ID) {}
        virtual bool runOnFunction(Function &F) override;
    };
}



#endif //VANGUARD_LOCALVANGUARD_H
