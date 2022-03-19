//
// Created by Jon Stephens on 3/19/22.
//

#include "IntraproceduralExample.h"

IntraproceduralExample::IntraproceduralExample() : IntraproceduralVanguard(ID) {

}


char IntraproceduralExample::ID = 0;
static RegisterPass<IntraproceduralExample> X("intra-example", "Intraprocedural Example",
                             true /* Only looks at CFG */,
                             true /* Analysis Pass */);