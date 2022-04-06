//
// Created by Jon Stephens on 3/19/22.
//

#include "SuicideDetector.h"
#include "SuicideAnalysis.h"

namespace Suicide {
    SuicideDetector::SuicideDetector() : IntraproceduralVanguard(ID) {
        const blockchain::Blockchain *chain = blockchain();
        analyzer = new SuicideAnalysis(chain);
        Vanguard::registerAnalysis(analyzer);
    }

    char SuicideDetector::ID = 0;
    static RegisterPass<SuicideDetector> X("suicide", "Basic Suicide Detector",
                                              true /* Only looks at CFG */,
                                              true /* Analysis Pass */);

}