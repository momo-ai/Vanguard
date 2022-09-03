//
// Created by Jon Stephens on 9/2/22.
//

#ifndef VANGUARD_BLKFUNCTION_H
#define VANGUARD_BLKFUNCTION_H

#include "Blockchain.h"
#include <program/Value.h>
#include <program/Type.h>
#include <string>
#include <list>
#include <utility>

namespace vanguard {
    enum Mutability {
        PURE,
        VIEW,
        PAYABLE,
        NONPAYABLE
    };

    enum Visibility {
        EXTERNAL,
        PUBLIC,
        INTERNAL,
        PRIVATE
    };

    template<class Domain>
    class BlkFunction : public Blockchain<Domain>::Function {
    public:
        template<typename ...Args>
        explicit BlkFunction(std::string name, std::string selector, bool isCnstr, Visibility vis, Mutability mut, std::vector<Variable *> params, std::vector<Variable *> rets, std::vector<std::string> mods, Args&&... args) : fnParams(std::move(params)), rets(std::move(rets)), mods(std::move(mods)), fnName(std::move(name)), isCnstr(isCnstr), vis(vis), mut(mut), Blockchain<Domain>::Function(std::forward<Args>(args)...) {};

        bool isHelper() const override {
            return false;
        }

        std::string name() const override {
            return fnName;
        }

        std::vector<Variable*> params() const override {
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

    private:
        std::string selector;
        std::vector<Variable*> fnParams;
        std::vector<Variable *> rets;
        std::vector<std::string> mods;
        std::string fnName;
        bool isCnstr;
        Visibility vis;
        Mutability mut;
    };
}

#endif //VANGUARD_BLKFUNCTION_H
