//
// Created by Jon Stephens on 4/3/22.
//

#include "VariableShadowingDetector.h"
#include "VariableShadowingAnalysis.h"

using namespace vanguard;
using namespace llvm;
using namespace blockchain;

namespace shadowing {
    VariableShadowingDetector::VariableShadowingDetector() : LocalVanguard(ID) {
        AARequirement *aa = AARequirement::getRequirement(*this);
        const Blockchain *blk = blockchain(aa);
        auto analysis = new VariableShadowingAnalysis(blk);
        registerAnalysis(analysis);
    }

    char VariableShadowingDetector::ID = 0;
    static RegisterPass<VariableShadowingDetector> X("var-shadowing", "Checks for Variable Shadowing",
                                                  true /* Only looks at CFG */,
                                                  true /* Analysis Pass */);
}