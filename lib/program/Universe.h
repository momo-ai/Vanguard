//
// Created by Jon Stephens on 9/18/22.
//

#ifndef VANGUARD_UNIVERSE_H
#define VANGUARD_UNIVERSE_H

#include "Base.h"

namespace vanguard {
    template<typename Domain>
    class Base<Domain>::Universe {
    public:
        Universe(std::vector<typename Domain::CompilationUnit *>  units) : programUnits(std::move(units)) {
            for(auto unit : programUnits) {
                unit->setUniverse(*((typename Domain::Universe *) this));
            }
        }

        Universe(const Universe&) = delete;

        const std::vector<typename Domain::CompilationUnit *> &units() const {
            return programUnits;
        }

    private:
        std::vector<typename Domain::CompilationUnit *> programUnits;
    };
}

#endif //VANGUARD_UNIVERSE_H
