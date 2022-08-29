//
// Created by Jon Stephens on 4/10/22.
//

#include "domain/libBlockchain/include/Ink/Ink.h"
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Instruction.h>
#include <llvm/Analysis/MemoryLocation.h>

#include <utility>
#include "domain/libBlockchain/include/Ink/InkModel.h"

namespace blockchain {
    Ink::Ink(BlockchainModel *blk2llvm, std::string &c, std::string &v, std::vector<BlkContract *> contracts, vanguard::AAWrapper &alias)
        : Blockchain(INK, blk2llvm, c, v, std::move(contracts)), alias(alias) {}

    bool Ink::allowsReentrancy() const {
        return true;
    }

    bool Ink::writesStorage(vanguard::Instruction &ins) {
        const llvm::Instruction& llvmIns = ins.unwrap();
        auto fn = llvmIns.getFunction();
        auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
        vanguard::Function* fnV = llvmToVanguard.translateFunction(fn);
        auto blkFn = findFunction(*fnV);
        if(blkFn == nullptr) {
            return false;
        }

        if(fn->arg_size() < 1) {
            throw std::runtime_error("Expected there to be at least one input to " + fn->getName().str());
        }

        auto selfArg = InkModel::getSelfRef(*blkFn, *fnV);
        llvm::MemoryLocation selfLoc = llvm::MemoryLocation::getAfter(selfArg);

        if(InkModel::isMemoryStore(ins)) {
            llvm::MemoryLocation storeLoc = InkModel::getStoreLocation(ins);
            llvm::Function* fnNoConst = const_cast<llvm::Function*>(fn);
            llvm::AAResults *aa = alias.request(*fnV);
            if(aa->alias(storeLoc, selfLoc) > llvm::AliasResult::MayAlias) {
                return true;
            }
        }

        if(auto call = llvm::dyn_cast<llvm::CallInst>(&llvmIns)) {
            auto fnc = call->getCalledFunction();
            auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
            vanguard::Function* fncV = llvmToVanguard.translateFunction(fn);
            //Can only store contract variables
            if(InkModel::isLazyStore(*fncV)) {
                return true;
            }
        }

        return false;
    }

    bool Ink::readsStorage(vanguard::Instruction &ins) {
        const llvm::Instruction& llvmIns = ins.unwrap();
        auto fn = llvmIns.getFunction(); // THE CULPRIT
        auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
        vanguard::Function* fnV = llvmToVanguard.translateFunction(fn);

        auto blkFn = findFunction(*fnV);
        if(blkFn == nullptr) {
            return false;
        }

        if(fn->arg_size() < 1) {
            throw std::runtime_error("Expected there to be at least one input to " + fn->getName().str());
        }

        auto selfArg = InkModel::getSelfRef(*blkFn, *fnV);
        llvm::MemoryLocation selfLoc = llvm::MemoryLocation::getAfter(selfArg);

        if(InkModel::isMemoryRead(ins)) {
            llvm::MemoryLocation readLoc = InkModel::getReadLocation(ins);

            llvm::AAResults *aa = alias.request(*fnV); // otherwise  alias.request(*fn), which throws error
            if(aa->alias(readLoc, selfLoc) > llvm::AliasResult::MayAlias) {
                return true;
            }
        }

        if(auto call = llvm::dyn_cast<llvm::CallInst>(&llvmIns)) {
            auto fn = call->getCalledFunction();
            auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
            vanguard::Function* fnV = llvmToVanguard.translateFunction(fn);

            //Can only store contract variables
            if(InkModel::isLazyGet(*fnV)) {
                return true;
            }
        }

        return false;
    }

    bool Ink::getsSender(vanguard::Instruction &ins) const {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(auto call = llvm::dyn_cast<llvm::CallInst>(&llvmIns)) {
            auto fn = call->getCalledFunction();
            auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
            vanguard::Function* fnV = llvmToVanguard.translateFunction(fn);

            if(InkModel::isMsgSender(*fnV)) {
                return true;
            }
        }

        return false;
    }

    bool Ink::getsValue(vanguard::Instruction &ins) const {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(auto call = llvm::dyn_cast<llvm::CallInst>(&llvmIns)) {
            auto fn = call->getCalledFunction();
            auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
            vanguard::Function* fnV = llvmToVanguard.translateFunction(fn);

            if(InkModel::isMsgValue(*fnV)) {
                return true;
            }
        }

        return false;
    }

    bool Ink::isSelfDestruct(vanguard::Instruction &ins) const {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(auto call = llvm::dyn_cast<llvm::CallInst>(&llvmIns)) {
            auto fn = call->getCalledFunction();
            auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
            vanguard::Function* fnV = llvmToVanguard.translateFunction(fn);

            if(InkModel::isSelfDestruct(*fnV)) {
                return true;
            }
        }

        return false;
    }
}