#ifndef VANGUARD_COMPILATIONUNIT_H
#define VANGUARD_COMPILATIONUNIT_H

#include "Base.h"

namespace vanguard{

    template<typename Domain>
    class Base<Domain>::CompilationUnit {
    public:
        explicit CompilationUnit(typename Domain::Factory &factory, const llvm::Module* mod): factory(factory), module(mod){}
        CompilationUnit(const CompilationUnit&) = delete;
        std::string name() {
            return module->getModuleIdentifier();
        }

        std::string sourceFile() {
            return module->getSourceFileName();
        }

        typename Domain::Value* findGlobalVariable(std::string name)  {
            //auto &llvmToVanguard = LLVMtoVanguard::getInstance();
            auto globalVariable = module->getGlobalVariable(llvm::StringRef(name), true);
            if (globalVariable == nullptr){
                return nullptr;
            }
            return factory.createVal(globalVariable);
        }

        virtual std::list<typename Domain::Value*> globalVariables() {
            //auto &llvmToVanguard = LLVMtoVanguard::getInstance();
            std::list<Value*> allGlobalVariables = {};
            for (auto gv= module->global_begin(); gv != module->global_end(); gv++){
                allGlobalVariables.push_back(factory.createVal(&*gv));
            }
            return allGlobalVariables;
        }

        virtual typename Domain::Function* findFunction(std::string name) const {
            //auto &llvmToVanguard = LLVMtoVanguard::getInstance();
            auto function = module->getFunction(llvm::StringRef(name));
            if (function == nullptr) {
                return nullptr;
            }
            return factory.createFn(function);
        }

        virtual std::list<typename Domain::Function *> functions() const {
            //auto &llvmToVanguard = LLVMtoVanguard::getInstance();
            std::list<typename Domain::Function*> allFunctions = {};
            for(auto &F: *module){
                allFunctions.push_back(factory.createFn(&F));
            }
            return allFunctions;
        }

        const llvm::Module* unwrap() {
            return module;
        }

    protected:
        //typename Domain::Function* findFn(std::string name) const;
        //virtual std::list<typename Domain::Function *> fns() const;
        typename Domain::Factory &factory;
    private:
        const llvm::Module* module;
    };

    /*template<typename Domain>
    Universe<Domain>::CompilationUnit::CompilationUnit(Factory &factory, const llvm::Module* mod): factory(factory), module(mod){}

    template<typename Domain>
    std::string Universe<Domain>::CompilationUnit::name(){
        return module->getModuleIdentifier();
    }

    template<typename Domain>
    std::string Universe<Domain>::CompilationUnit::sourceFile(){
        return module->getSourceFileName();
    }

    template<typename Domain>
    typename Domain::Function* Universe<Domain>::CompilationUnit::findFunction(std::string name) const {
        //auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto function = module->getFunction(llvm::StringRef(name));
        if (function == nullptr) {
            return nullptr;
        }
        return factory.createFn(function);
    }

    template<typename Domain>
    typename Domain::Value* Universe<Domain>::CompilationUnit::findGlobalVariable(std::string name) {
        //auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto globalVariable = module->getGlobalVariable(llvm::StringRef(name), true);
        if (globalVariable == nullptr){
            return nullptr;
        }
        return factory.createVal(globalVariable);
    }

    template<typename Domain>
    std::list<typename Domain::Function*> Universe<Domain>::CompilationUnit::functions() const {
        //auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<typename Domain::Function*> allFunctions = {};
        for(auto &F: *module){
            allFunctions.push_back(factory.createFn(&F));
        }
        return allFunctions;
    }

    template<typename Domain>
    std::list<typename Domain::Value*> Universe<Domain>::CompilationUnit::globalVariables(){
        //auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Value*> allGlobalVariables = {};
        for (auto gv= module->global_begin(); gv != module->global_end(); gv++){
            allGlobalVariables.push_back(factory.createVal(&*gv));
        }
        return allGlobalVariables;
    }

    template<typename Domain>
    const llvm::Module* Universe<Domain>::CompilationUnit::unwrap() {
        return module;
    }*/

}
#endif