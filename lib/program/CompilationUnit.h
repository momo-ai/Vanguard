#ifndef VANGUARD_PROGRAM_COMPILATION_UNIT_H
#define VANGUARD_PROGRAM_COMPILATION_UNIT_H

#include "Value.h"
#include "Function.h"
#include <llvm/IR/Module.h>

namespace vanguard{
    class CompilationUnit{
    private:
        const llvm::Module& module;
    public:
        explicit CompilationUnit(const llvm::Module& mod);

        CompilationUnit(const CompilationUnit&) = delete;

        std::string name();

        std::string sourceFile();

        Function* findFunction(std::string name);

        Value* findGlobalVariable(std::string name);

        std::list<Function *> functions();

        std::list<Value*> globalVariables();

        const llvm::Module& unwrap();
    };
}

#endif //VANGUARD_PROGRAM_COMPILATION_UNIT_H