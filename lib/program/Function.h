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

        std::string getName();

        std::list<Argument*> getParams();

        std::list<Type *> getParamTypes();

        Type* getReturnType();

        bool hasBody();

        Block* getBody();

        std::list<Instruction*> getInstructionsList();

        std::list<Block *> getAllBlocks();

        const llvm::Function &unwrap();

    private:
        const llvm::Function &function;
    };

}

#endif
