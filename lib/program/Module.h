#ifndef VANGUARD_PROGRAM_MODULE_H
#define VANGUARD_PROGRAM_MODULE_H

#include "Value.h"
#include "Function.h"
#include <unordered_set>
#include <llvm/IR/Module.h>

namespace vanguard{
    class Module{
        public:
            Module(llvm::Module& mod);

            const std::string getModuleName();

            const std::string getSourceFileName();

            Function* getFunction(std::string name);

            Value* getGlobalVariable(std::string name);

            std::unordered_set<Function *> getAllFunctions();

            std::unordered_set<Value*> getAllGlobalVariables();

            llvm::Module* unwrap();

        private:
            llvm::Module& module;

    };
}

#endif