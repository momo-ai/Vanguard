#ifndef VANGUARD_PROGRAM_COMPILATION_UNIT_H
#define VANGUARD_PROGRAM_COMPILATION_UNIT_H

#include "Value.h"
#include "Function.h"
#include <unordered_set>
#include <llvm/IR/Module.h> 

namespace vanguard{
    class CompilationUnit{
    private:
        const llvm::Module& module;
    public:
        explicit CompilationUnit(const llvm::Module& mod);

        CompilationUnit(const CompilationUnit&) = delete;

        std::string getModuleName();

        std::string getSourceFileName();

        Function* getFunction(std::string name);

        Value* getGlobalVariable(std::string name);

        std::unordered_set<Function *> getAllFunctions();

        std::unordered_set<Value*> getAllGlobalVariables();

        llvm::Module* unwrap();
    };
}

#endif //VANGUARD_PROGRAM_COMPILATION_UNIT_H