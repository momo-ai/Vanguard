#ifndef VANGUARD_PROGRAM_MODULE_H
#define VANGUARD_PROGRAM_MODULE_H

#include "Function.h"
#include <unordered_set>
#include <llvm/IR/Module.h>

namespace vanguard{
    class Module{
    private:
        llvm::Module& module;
    public:
        Module(llvm::Module& mod);

        const std::string getModuleName();

        const std::string getSourceFileName();

        Function* getFunction(std::string name);

        llvm::GlobalVariable* getGlobalVariable(std::string name);

        std::unordered_set<Function *> getAllFunctions();

        llvm::Module::GlobalListType* getAllGlobalVariables();

    };
}

#endif