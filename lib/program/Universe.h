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
        Universe(typename Domain::Factory &factory, std::vector<typename Domain::CompilationUnit *>  units) : fact(factory), programUnits(std::move(units)) {
            for(auto unit : programUnits) {
                unit->setUniverse(*((typename Domain::Universe *) this));
            }
        }

        const std::vector<typename Domain::CompilationUnit *> &units() const {
            return programUnits;
        }

        typename Domain::Factory &factory() {
            return fact;
        }

    protected:

        typename Domain::Factory &fact;
    private:
        std::vector<typename Domain::CompilationUnit *> programUnits;
    };
}

#endif //VANGUARD_UNIVERSE_H
