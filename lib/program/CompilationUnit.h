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
            std::list<typename Domain::Value*> allGlobalVariables = {};
            for (auto gv= module->global_begin(); gv != module->global_end(); gv++){
                allGlobalVariables.push_back(factory.createVal(&*gv));
            }
            return allGlobalVariables;
        }

        virtual typename Domain::Function* findFunction(std::string name) const {
            //auto &llvmToVanguard = LLVMtoVanguard::getInstance();
            auto function = module->getFunction(llvm::StringRef(name));
            if (function != nullptr) {
                return factory.createFn(function);
            }

            for (auto fn : this->functions()){
                if (fn->name() == name){
                    return fn;
                }
            }

            return nullptr;
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

        typename Domain::Universe *universe() {
            return uni;
        }

        void setUniverse(typename Domain::Universe &universe) {
            if(uni == nullptr) {
                uni = &universe;
            }
        }

    protected:
        //typename Domain::Function* findFn(std::string name) const;
        //virtual std::list<typename Domain::Function *> fns() const;
        typename Domain::Factory &factory;
        typename Domain::Universe *uni;
    private:
        const llvm::Module* module;
    };

}
#endif