//
// Created by Jon Stephens on 8/20/22.
//

#include "Universe.h"
#include "UnitFactory.h"
#include <utility>

namespace vanguard {
    Universe::Universe(UnitFactory &factory, const std::vector<std::unique_ptr<llvm::Module>>& modules){
        for(auto &mod : modules) {
            programUnits.push_back(factory.createUnit(mod.get()));
        }
    }

    const std::vector<Universe::CompilationUnit *> &Universe::units() {
        return programUnits;
    }
}