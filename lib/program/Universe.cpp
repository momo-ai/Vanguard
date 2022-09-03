//
// Created by Jon Stephens on 8/20/22.
//

#include "Universe.h"
#include "UnitFactory.h"
#include <utility>

namespace vanguard {
    Universe::Universe(UnitFactory &factory, std::vector<CompilationUnit *>  units) : programUnits(std::move(units)) {}

    const std::vector<Universe::CompilationUnit *> &Universe::units() const {
        return programUnits;
    }
}