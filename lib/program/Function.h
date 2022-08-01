#ifndef VANGUARD_PROGRAM_FUNCTION_H
#define VANGUARD_PROGRAM_FUNCTION_H

#include "llvm/IR/Function.h"
#include <list>
#include <string>

namespace vanguard {
    class Instruction;

    class Function{
        
    public:
        Function(llvm::Function& func);

        std::string getName();

        bool getParams();

        llvm::Type* getReturnType();

        bool hasBody();

        Block* getBody();

        std::list<Instruction*> getInstructionsList();

    private:
        llvm::Function& function;        
    };

}

#endif