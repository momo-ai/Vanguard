//
// Created by Jon Stephens on 8/20/22.
//

#ifndef VANGUARD_UNIVERSE_H
#define VANGUARD_UNIVERSE_H

#include <vector>
#include <llvm/IR/Module.h>

namespace vanguard {
    class UnitFactory;

    class Universe {
    public:
        class CompilationUnit;
        class Function;
        class Block;
        class Instruction;

        explicit Universe(UnitFactory &factory, const std::vector<std::unique_ptr<llvm::Module>>& modules);
        const std::vector<CompilationUnit *> &units();

    private:
        std::vector<CompilationUnit *> programUnits;
    };
}



#endif //VANGUARD_UNIVERSE_H
