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

    std::unordered_set<Function*> CompilationUnit::getAllFunctions(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::unordered_set<Function*> allFunctions = {};
        for(auto &F: module){
            allFunctions.insert(llvmToVanguard.translateFunction(&F));
        }
        return allFunctions;
    }

    std::unordered_set<Value*> CompilationUnit::getAllGlobalVariables(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::unordered_set<Value*> allGlobalVariables = {};
        for (auto gv= module.global_begin(); gv != module.global_end(); gv++){
            allGlobalVariables.insert(llvmToVanguard.translateValue(&*gv));
        }
        return allGlobalVariables;
    }

    const llvm::Module& CompilationUnit::unwrap() {
        return module;
    }

}