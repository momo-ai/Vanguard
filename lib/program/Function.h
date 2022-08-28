#ifndef VANGUARD_PROGRAM_FUNCTION_H
#define VANGUARD_PROGRAM_FUNCTION_H

#include "Type.h"
#include "Value.h"
#include "llvm/IR/Function.h"
#include "Type.h"
#include <list>
#include <string>

namespace vanguard {

    class Instruction;
    class Block;

    class Function{    
    public:
        explicit Function(const llvm::Function &func);

        Function(const Function&) = delete;

        std::string name();

        std::list<Argument*> params();

        Type* returnType();

        bool hasBody();

        Block* body();

        std::list<Instruction*> instructions();

        std::list<Block *> blocks();

        const llvm::Function &unwrap();

    private:
        const llvm::Function &function;
    };

}

#endif
