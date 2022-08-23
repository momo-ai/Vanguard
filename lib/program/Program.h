//
// Created by Jon Stephens on 8/20/22.
//

#ifndef VANGUARD_PROGRAM_H
#define VANGUARD_PROGRAM_H

#include <vector>
#include "CompilationUnit.h"

namespace vanguard {
    class Program {
    public:
        explicit Program(std::vector<CompilationUnit *> &units);
        const std::vector<CompilationUnit *> &units();

    private:
        std::vector<CompilationUnit *> programUnits;
    };
}



#endif //VANGUARD_PROGRAM_H
