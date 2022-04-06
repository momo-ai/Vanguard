//
// Created by Jon Stephens on 3/19/22.
//

#include "ReentrancyDetector.h"
#include "ReentrancyAnalysis.h"

namespace Reentrancy {
    ReentrancyDetector::ReentrancyDetector() : IntraproceduralVanguard(ID) {
        const blockchain::Blockchain *chain = blockchain();
        analyzer = new ReentrancyAnalysis(chain);
        Vanguard::registerAnalysis(analyzer);
    }

    char ReentrancyDetector::ID = 0;
    static RegisterPass<ReentrancyDetector> X("reentrancy", "Basic Reentrancy Detector",
                                              true /* Only looks at CFG */,
                                              true /* Analysis Pass */);

}