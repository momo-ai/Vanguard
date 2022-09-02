#ifndef VANGUARD_PROGRAM_COMPILATION_UNIT_H
#define VANGUARD_PROGRAM_COMPILATION_UNIT_H

#include "Universe.h"
#include "Value.h"
#include "Function.h"
#include <llvm/IR/Module.h>

namespace vanguard{
    class Universe::CompilationUnit {
    private:
        const llvm::Module& module;
    public:
        explicit CompilationUnit(UnitFactory &factory, const llvm::Module& mod);

        CompilationUnit(const CompilationUnit&) = delete;

        std::string name();

        std::string sourceFile();

        Universe::Function* findFunction(std::string name);

        Value* findGlobalVariable(std::string name);

        virtual std::list<Universe::Function *> functions();

        virtual std::list<Value*> globalVariables();

        const llvm::Module& unwrap();

    protected:
        UnitFactory &factory;
    };
}

#endif //VANGUARD_PROGRAM_COMPILATION_UNIT_H