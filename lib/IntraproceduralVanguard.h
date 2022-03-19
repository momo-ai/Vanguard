//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_INTRAPROCEDURALVANGUARD_H
#define VANGUARD_INTRAPROCEDURALVANGUARD_H

#include "llvm/Pass.h"
#include "Analysis.h"
#include "Vanguard.h"

namespace vanguard {
    class IntraproceduralVanguard : public ModulePass, public Vanguard {
    public:
        IntraproceduralVanguard(char &ID) : ModulePass(ID) {}
        virtual bool runOnModule(Module &m) override;
    private:
    };
}


#endif //VANGUARD_INTRAPROCEDURALVANGUARD_H
