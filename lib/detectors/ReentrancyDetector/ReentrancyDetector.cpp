//
// Created by Jon Stephens on 3/19/22.
//

#include "ReentrancyDetector.h"
#include "ReentrancyAnalysis.h"

namespace Reentrancy {
    ReentrancyDetector::ReentrancyDetector() : IntraproceduralVanguard(ID) {
        AARequirement *aa = AARequirement::getRequirement(*this);
        const blockchain::Blockchain *chain = blockchain(aa);
        analyzer = new ReentrancyAnalysis(chain);
        Vanguard::registerAnalysis(analyzer);
    }

    char ReentrancyDetector::ID = 0;
    static RegisterPass<ReentrancyDetector> X("reentrancy", "Basic Reentrancy Detector",
                                              true /* Only looks at CFG */,
                                              true /* Analysis Pass */);

}