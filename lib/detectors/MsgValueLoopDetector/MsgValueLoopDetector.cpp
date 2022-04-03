//
// Created by Benjamin Mariano on 4/3/22.
//

#include "MsgValueLoopDetector.h"

namespace MsgValueLoop {
    MsgValueLoopDetector::MsgValueLoopDetector() : IntraproceduralVanguard(ID) {
        const blockchain::Blockchain *chain = blockchain();
        analyzer = new MsgValueLoopAnalysis(chain);
        Vanguard::registerAnalysis(analyzer);
    }

    MsgValueLoopDetector::~MsgValueLoopDetector() {
        delete analyzer;
    }

    char MsgValueLoopDetector::ID = 0;
    static RegisterPass<MsgValueLoopDetector> X("msg_value_loop", "Basic uninitialized state detector",
                                                      true /* Only looks at CFG */,
                                                      true /* Analysis Pass */);

}