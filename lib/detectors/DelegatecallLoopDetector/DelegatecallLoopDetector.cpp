//
// Created by Benjamin Mariano on 4/3/22.
//

#include "DelegatecallLoopDetector.h"

namespace DelegatecallLoop {
    DelegatecallLoopDetector::DelegatecallLoopDetector() : IntraproceduralVanguard(ID) {
        AARequirement *aa = AARequirement::getRequirement(*this);
        const blockchain::Blockchain *chain = blockchain(aa);
        analyzer = new DelegatecallLoopAnalysis(chain);
        Vanguard::registerAnalysis(analyzer);
    }

    char DelegatecallLoopDetector::ID = 0;
    static RegisterPass<DelegatecallLoopDetector> X("delegatecall_loop", "Detects use of delegatecall in payable loop",
                                                    true /* Only looks at CFG */,
                                                    true /* Analysis Pass */);

}
