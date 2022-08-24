#include "CompilationUnit.h"
#include "LLVMtoVanguard.h"

namespace vanguard{

    CompilationUnit::CompilationUnit(const llvm::Module& mod): module(mod){}

    std::string CompilationUnit::getModuleName(){
        return module.getModuleIdentifier();
    }

    std::string CompilationUnit::getSourceFileName(){
        return module.getSourceFileName();
    }

    Function* CompilationUnit::getFunction(std::string name){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto function = module.getFunction(llvm::StringRef(name));
        if (function == nullptr) {
            return nullptr;
        }
        return llvmToVanguard.translateFunction(function);
    }

    Value* CompilationUnit::getGlobalVariable(std::string name){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto globalVariable = module.getGlobalVariable(llvm::StringRef(name), true);
        if (globalVariable == nullptr){
            return nullptr;
        }
        return llvmToVanguard.translateValue(globalVariable);
    }

    std::list<Function*> CompilationUnit::getAllFunctions(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Function*> allFunctions = {};
        for(auto &F: module){
            allFunctions.push_back(llvmToVanguard.translateFunction(&F));
        }
        return allFunctions;
    }

    std::list<Value*> CompilationUnit::getAllGlobalVariables(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Value*> allGlobalVariables = {};
        for (auto gv= module.global_begin(); gv != module.global_end(); gv++){
            allGlobalVariables.push_back(llvmToVanguard.translateValue(&*gv));
        }
        return allGlobalVariables;
    }

    const llvm::Module& CompilationUnit::unwrap() {
        return module;
    }

}