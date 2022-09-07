//
// Created by Kostas Ferles on 8/29/22.
//

#include "../include/NearToLLVM.h"
#include "../include/BlkContract.h"
#include "../../../analysis/llvm-utils/LLVMUtils.h"

namespace blockchain {

    void replace_all(std::string &s, const std::string &toRepl, const std::string &replStr) {
        std::string buf;
        std::size_t pos = 0;
        std::size_t prevPos = 0;
        std::size_t toReplSize = toRepl.size();

        buf.reserve(s.size());

        while ((pos = s.find(toRepl, pos)) != std::string::npos) {
            buf.append(s, prevPos, pos - prevPos);
            buf += replStr;
            prevPos = (pos += toReplSize);
        }

        buf.append(s, prevPos, s.size() - prevPos);
        s.swap(buf);
    }

    std::string clipRustHash(std::string funcName) {
        return funcName.substr(0, funcName.size() - 19);
    }

    void fixDemangler(std::string &funcDemName) {
        replace_all(funcDemName, "$LT$", "<");
        replace_all(funcDemName, "$GT$", ">");
        replace_all(funcDemName, "..", "::");
        replace_all(funcDemName, "$u20$", " ");

        if (funcDemName[0] == '_')
            funcDemName.replace(0, 1, "");
    }

    NearToLLVM::NearToLLVM(vanguard::AAWrapper &alias) : alias(alias) {}

    bool NearToLLVM::isTranslation(const BlkFunction &blockchainFn, vanguard::Function &fun) const {
        auto demangledName = clipRustHash(analysis::LLVMUtils::demangleFunction(&fun));

        if (demangledName.find('$') != std::string::npos)
            fixDemangler(demangledName);

        return demangledName == blockchainFn.blkName();
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