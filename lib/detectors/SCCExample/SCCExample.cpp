//
// Created by Jon Stephens on 3/19/22.
//

#include "SCCExample.h"

SCCExample::SCCExample() : SCCVanguard(ID) {}

char SCCExample::ID = 0;
static RegisterPass<SCCExample> X("scc-example", "SCC Example",
                                              true /* Only looks at CFG */,
                                              true /* Analysis Pass */);