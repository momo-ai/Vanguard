//
// Created by Jon Stephens on 9/18/22.
//

#ifndef VANGUARD_LIBBLOCKCHAIN_FUNCTION_H
#define VANGUARD_LIBBLOCKCHAIN_FUNCTION_H

#include "Blockchain.h"

namespace vanguard {
    template<typename Base, typename Domain>
    class Blockchain<Base, Domain>::Function : public Base::Function {
    public:
        template<typename ...Args>
        explicit Function(std::string name, std::string selector, bool isCnstr, Visibility vis, Mutability mut, std::vector<vanguard::Variable<Domain> *> params, std::vector<vanguard::Variable<Domain> *> rets, std::vector<std::string> mods, Args&&... args) : helper(false), parentContract(nullptr), fnParams(std::move(params)), rets(std::move(rets)), mods(std::move(mods)), fnName(std::move(name)), isCnstr(isCnstr), vis(vis), mut(mut), sel(std::move(selector)), Base::Function(std::forward<Args>(args)...) {};

        template<typename ...Args>
        explicit Function(Args&&... args) : helper(true), parentContract(nullptr), fnParams({}), rets({}), mods({}), fnName(), isCnstr(false), vis(PUBLIC), mut(NONPAYABLE), sel(""), Base::Function(std::forward<Args>(args)...) {};

        bool isHelper() const {
            return helper;
        }

        std::string name() const override {
            if(helper) {
                return Base::Function::name();
            }
            return fnName;
        }

        std::string selector() const {
            return sel;
        }

        std::vector<vanguard::Variable<Domain>*> params() const override {
            if(helper) {
                return Base::Function::params();
            }
            return fnParams;
        }

        std::vector<std::string> modifiers() const {
            return mods;
        }

        //virtual Type* returnType();

        bool isConstructor() const {
            return isCnstr;
        }

        Visibility visibility() const {
            return vis;
        }

        Mutability mutability() const {
            return mut;
        }

        void wrap(const llvm::Function *fn) {
            this->function = fn;
        }

        typename Domain::Contract *contract() {
            return parentContract;
        }

        void setContract(typename Domain::Contract *contract) {
            if(parentContract == nullptr) {
                parentContract = contract;
            }
        }

    private:
        bool helper;
        std::string sel;
        std::vector<vanguard::Variable<Domain> *> fnParams;
        std::vector<vanguard::Variable<Domain> *> rets;
        std::vector<std::string> mods;
        std::string fnName;
        bool isCnstr;
        Visibility vis;
        Mutability mut;
        typename Domain::Contract *parentContract;
    };
}


#endif //VANGUARD_FUNCTION_H
