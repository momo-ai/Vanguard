//
// Created by Kostas Ferles on 8/30/22.
//

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Metadata.h>
#include <llvm/IR/DebugInfoMetadata.h>
#include <iostream>
#include <set>

#include "../include/Near.h"
#include "../../../analysis/llvm-utils/LLVMUtils.h"

namespace blockchain {

    Near::Near(BlockchainToLLVM *blk2llvm, string &c, string &v, vector<BlkContract *> *contracts, vanguard::AAWrapper &alias) : Blockchain(INK, blk2llvm, c, v, contracts), alias(alias) {}

    bool Near::allowsReentrancy() const {
        return true;
    }

    bool Near::writesStorage(vanguard::Instruction &ins) {
        auto &llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
        auto insFun = llvmToVanguard.getInstructionFunction(&ins);

        auto selfVal = analysis::LLVMUtils::getNamedFunctionArg(insFun, "self");

        if (selfVal == nullptr)
            selfVal = analysis::LLVMUtils::getFunctionArg(insFun, 0);

        assert(("Could not find self argument" && selfVal != nullptr));
        assert(("Invalid pointer type" && dynamic_cast<vanguard::PointerType *>(selfVal->type())));

        return analysis::LLVMUtils::writesMemTo(&ins, selfVal);
    }

    bool Near::readsStorage(vanguard::Instruction &ins) {
        auto &llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
        auto cUnit = llvmToVanguard.getInstructionCompUnit(&ins);

        vanguard::Function &vFn = *llvmToVanguard.getInstructionFunction(&ins);
        auto blkFn = findFunction(vFn);

        if(blkFn == nullptr) {
            return false;
        }

        auto selfVal = analysis::LLVMUtils::getNamedFunctionArg(&vFn, "self");

        assert(("Could not find self argument" && selfVal != nullptr));

        return analysis::LLVMUtils::readsMemFrom(&ins, selfVal);
    }

    bool Near::getsSender(vanguard::Instruction &ins) const {
        // detect calls to predecessor_account_id: (https://docs.rs/near-sdk/latest/near_sdk/env/fn.predecessor_account_id.html#)???
        throw new std::runtime_error("Unsupported Operation");
    }

    bool Near::getsValue(vanguard::Instruction &ins) const {
        throw new std::runtime_error("Unsupported Operation");
    }

    bool Near::isSelfDestruct(vanguard::Instruction &ins) const {
        throw new std::runtime_error("Unsupported Operation");
    }

    size_t Near::findVarOffset(BlkVariable &var, BlkContract &contract, vanguard::CompilationUnit &cu) {

        map<string, size_t> &contractVars = varOffsets[&contract];
        if (contractVars.find(var.name()) == contractVars.end()) {
            std::string contrName = contract.blkName();
            std::string varName = var.name();

            auto mdMap = analysis::LLVMUtils::getMetadata(&cu);
            for (auto mNode : mdMap[llvm::MDNode::MetadataKind::DICompositeTypeKind]) {
                auto diTy = llvm::dyn_cast<llvm::DICompositeType>(mNode);

                if (diTy->getName().str() == contract.blkName())
                {
                    std::function<bool(llvm::Metadata*)> pred = [&diTy](auto n){
                        if (auto derType = llvm::dyn_cast<llvm::DIDerivedType>(n))
                            return derType->getScope() == diTy;
                        return false;
                    };

                    auto foundNodes = analysis::LLVMUtils::findNodesUnder(diTy, pred);
                    std::vector<llvm::Metadata*> foundAsVec(foundNodes.begin(), foundNodes.end());
                    std::sort(foundAsVec.begin(),
                              foundAsVec.end(),
                              [](auto a, auto b) {
                                 return llvm::dyn_cast<llvm::DIDerivedType>(a)->getOffsetInBits() < llvm::dyn_cast<llvm::DIDerivedType>(b)->getOffsetInBits();
                              }
                    );

                    for (size_t i = 0, e = foundAsVec.size(); i < e; i++) {
                        auto varI = llvm::dyn_cast<llvm::DIDerivedType>(foundAsVec[i]);
                        contractVars[varI->getName().str()] = i;
                    }
                }
            }
        }

        return contractVars[var.name()];
    }

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

    void fixDemangler(std::string &funcDemName) {
        replace_all(funcDemName, "$LT$", "<");
        replace_all(funcDemName, "$GT$", ">");
        replace_all(funcDemName, "..", "::");
        replace_all(funcDemName, "$u20$", " ");

        if (funcDemName[0] == '_')
            funcDemName.replace(0, 1, "");
    }

    std::string clipRustHash(const std::string& funcName) {
        return funcName.substr(0, funcName.size() - 19);
    }

    std::string Near::demangleRustName(const vanguard::Function& fun) {
        auto demangledName = clipRustHash(analysis::LLVMUtils::demangleFunction(&fun));

        if (demangledName.find('$') != std::string::npos)
            fixDemangler(demangledName);

        return demangledName;
    }
}