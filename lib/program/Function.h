#ifndef VANGUARD_PROGRAM_FUNCTION_H
#define VANGUARD_PROGRAM_FUNCTION_H

#include "Universe.h"
#include "Type.h"
#include "Value.h"
#include "llvm/IR/Function.h"
#include "Type.h"
#include <list>
#include <string>

namespace vanguard {

    class Universe::Function{
    public:
        explicit Function(UnitFactory &factory, const llvm::Function &func);

        Function(const Function&) = delete;

        std::string name();

        virtual std::list<Argument*> params();

        virtual Type* returnType();

        bool hasBody();

        Block* body();

        virtual std::list<Instruction*> instructions();

        virtual std::list<Block *> blocks();

        const llvm::Function &unwrap();

    protected:
        const llvm::Function &function;
        UnitFactory &factory;
    };

}

#endif
