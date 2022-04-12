//
// Created by Jon Stephens on 3/19/22.
//

#include "UninitializedStateDetector.h"
#include "UninitializedStateAnalysis.h"

namespace UninitializedState {
    UninitializedStateDetector::UninitializedStateDetector() : IntraproceduralVanguard(ID) {
        AARequirement *aa = AARequirement::getRequirement(*this);
        const blockchain::Blockchain *chain = blockchain(aa);
        analyzer = new UninitializedStateAnalysis(chain);
        Vanguard::registerAnalysis(analyzer);
    }

    char UninitializedStateDetector::ID = 0;
    static RegisterPass<UninitializedStateDetector> X("uninitialized_state", "Basic uninitialized state detector",
                                                      true /* Only looks at CFG */,
                                                      true /* Analysis Pass */);

}