#ifndef VANGUARD_PROGRAM_FUNCTION_H
#define VANGUARD_PROGRAM_FUNCTION_H

#include "llvm/IR/Function.h"
#include "Type.h"
#include <list>
#include <string>

namespace vanguard {

    class Instruction;
    class Block;

    class Function{    
    public:
        explicit Function(const llvm::Function& func);

        Function(const Function&) = delete;

        std::string getName();

        bool getParams();

        Type* getReturnType();

        bool hasBody();

        Block* getBody();

        std::list<Instruction*> getInstructionsList();

    private:
        const llvm::Function& function;
    };

}

#endif
