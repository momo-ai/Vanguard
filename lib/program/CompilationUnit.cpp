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
        return llvmToVanguard.translateFunction(module.getFunction(llvm::StringRef(name)));
    }

    Value* CompilationUnit::getGlobalVariable(std::string name){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(module.getGlobalVariable(llvm::StringRef(name)));
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

}