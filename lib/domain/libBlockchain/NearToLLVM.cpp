//
// Created by Kostas Ferles on 8/29/22.
//

#include "../include/NearToLLVM.h"
#include "../include/BlkContract.h"
#include "../../../analysis/llvm-utils/LLVMUtils.h"

namespace blockchain {

    NearToLLVM::NearToLLVM(vanguard::AAWrapper &alias) : alias(alias) {}

    bool NearToLLVM::isTranslation(const BlkFunction &blockchainFn, vanguard::Function &fun) const {
        return Near::demangleRustName(fun) == blockchainFn.blkName();
    }

    bool NearToLLVM::isAnyExternalCall(vanguard::Function &fun) const {
        // TODO: Needs to be refined to also support low-level calls.
        if (auto blkFun = near->findFunction(fun)) {
            return ((BlkContract *)blkFun->parent())->isExternal();
        }
        return false;
    }

    bool NearToLLVM::isCall(vanguard::Function &fun) const {
        return near->findFunction(fun) != nullptr;
    }

    bool NearToLLVM::isStaticCall(vanguard::Function &llvmFn) const {
        throw std::runtime_error("unsupported operation");
    }

    bool NearToLLVM::isDelegateCall(vanguard::Function &llvmFn) const {
        throw std::runtime_error("unsupported operation");
    }

    bool NearToLLVM::writesVariable(const BlkVariable &var, vanguard::Instruction &ins) const {
        throw std::runtime_error("to be implemented");
    }

    bool NearToLLVM::readsVariable(const BlkVariable &var, vanguard::Instruction &ins) const {
        throw std::runtime_error("to be implemented");
    }

    void NearToLLVM::setNear(blockchain::Near *nearObj) {
        this->near = nearObj;
    }
}