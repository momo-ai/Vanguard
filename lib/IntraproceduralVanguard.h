//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_INTRAPROCEDURALVANGUARD_H
#define VANGUARD_INTRAPROCEDURALVANGUARD_H

#include <unordered_set>
#include "llvm/Pass.h"
#include "Analysis.h"
#include "Vanguard.h"
using namespace std;
using namespace llvm;

namespace vanguard {
    class IntraproceduralVanguard : public ModulePass, public Vanguard {
    public:
        explicit IntraproceduralVanguard(char &ID) : ModulePass(ID) {}
        bool runOnModule(Module &m) override;
    };
}


#endif //VANGUARD_INTRAPROCEDURALVANGUARD_H
