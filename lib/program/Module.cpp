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

    Function* Module::getFunction(std::string name){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateFunction(module.getFunction(llvm::StringRef(name)));
    }

    Value* Module::getGlobalVariable(std::string name){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateValue(module.getGlobalVariable(llvm::StringRef(name)));
    }

    std::unordered_set<Function*> Module::getAllFunctions(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        std::unordered_set<Function*> allFunctions = {};
        for(llvm::Function& F: module){
            allFunctions.insert(llvmToVanguard->translateFunction(&F));
        }
        return allFunctions;
    }

    std::unordered_set<Value*> Module::getAllGlobalVariables(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        std::unordered_set<Value*> allGlobalVariables = {};
        for (auto gv= module.global_begin(); gv != module.global_end(); gv++){
            allGlobalVariables.insert(llvmToVanguard->translateValue(&*gv));
        }
        return allGlobalVariables;
    }

    llvm::Module* Module::unwrap(){
        return &module;
    }

}