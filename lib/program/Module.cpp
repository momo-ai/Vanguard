#include "Module.h"
#include "LLVMtoVanguard.h"

namespace vanguard{

    Module::Module(llvm::Module& mod): module(mod){}

    const std::string Module::getModuleName(){
        return module.getModuleIdentifier();
    }

    const std::string Module::getSourceFileName(){
        return module.getSourceFileName();
    }

    vanguard::Function* Module::getFunction(std::string name){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateFunction(module.getFunction(llvm::StringRef(name)));
    }

    llvm::GlobalVariable* Module::getGlobalVariable(std::string name){
        return module.getGlobalVariable(llvm::StringRef(name));
    }

    std::unordered_set<Function*> Module::getAllFunctions(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        std::unordered_set<Function*> allFunctions = {};
        for(llvm::Function& F: module){
            allFunctions.insert(llvmToVanguard->translateFunction(&F));
        }
        return allFunctions;
    }

    llvm::Module::GlobalListType* Module::getAllGlobalVariables(){
        return &(module.getGlobalList());
    }

}