//
// Created by Benjamin Mariano on 4/3/22.
//

#include "MsgValueLoopDetector.h"

namespace MsgValueLoop {
    MsgValueLoopDetector::MsgValueLoopDetector() : IntraproceduralVanguard(ID) {
        AARequirement *aa = AARequirement::getRequirement(*this);
        const blockchain::Blockchain *chain = blockchain(aa);
        analyzer = new MsgValueLoopAnalysis(chain);
        Vanguard::registerAnalysis(analyzer);
    }

    char MsgValueLoopDetector::ID = 0;
    static RegisterPass<MsgValueLoopDetector> X("msg_value_loop", "Detects use of msg.value in loop",
                                                      true /* Only looks at CFG */,
                                                      true /* Analysis Pass */);

}
