//
// Created by Jon Stephens on 3/19/22.
//

#include "IntraproceduralExample.h"
#include "ModPrint.h"

namespace IntraExample {
    IntraproceduralExample::IntraproceduralExample() : IntraproceduralVanguard(ID) {
        printer = new ModPrint();
        Vanguard::registerAnalysis(printer);
    }

    IntraproceduralExample::~IntraproceduralExample() {
        delete printer;
    }

    char IntraproceduralExample::ID = 0;
    static RegisterPass<IntraproceduralExample> X("intra-example", "Intraprocedural Example",
                                                  true /* Only looks at CFG */,
                                                  true /* Analysis Pass */);

}