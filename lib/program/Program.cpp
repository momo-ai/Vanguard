//
// Created by Jon Stephens on 8/20/22.
//

#include "Program.h"

namespace vanguard {
    Program::Program(std::vector<CompilationUnit *> &units) : programUnits(units) {}

    const std::vector<CompilationUnit *> &Program::units() {
        return programUnits;
    }
}