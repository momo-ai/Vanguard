//
// Created by Jon Stephens on 3/19/22.
//

#include "SCCExample.h"

namespace sccexample {
    SCCExample::SCCExample() : SCCVanguard(ID) {
        printer = new ModPrint();
        Vanguard::registerAnalysis(printer);
    }
}

char sccexample::SCCExample::ID = 0;
static RegisterPass<sccexample::SCCExample> X("scc-example", "SCC Example",
                                              true /* Only looks at CFG */,
                                              true /* Analysis Pass */);