//
// Created by Jon Stephens on 4/10/22.
//

#include "../include/Ink.h"
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Instruction.h>
#include <llvm/Analysis/MemoryLocation.h>
#include "../include/InkToLLVM.h"

namespace blockchain {
    Ink::Ink(BlockchainToLLVM *blk2llvm, string &c, string &v, vector<BlkContract *> *contracts, AAWrapper &alias) : Blockchain(INK, blk2llvm, c, v, contracts), alias(alias) {}

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
            throw runtime_error("Expected there to be at least one input to " + fn->getName().str());
        }

        auto selfArg = InkToLLVM::getSelfRef(*blkFn, *fnV);
        llvm::MemoryLocation selfLoc = llvm::MemoryLocation::getAfter(selfArg);

        if(InkToLLVM::isMemoryStore(ins)) {
            llvm::MemoryLocation storeLoc = InkToLLVM::getStoreLocation(ins);
            llvm::Function* fnNoConst = const_cast<llvm::Function*>(fn);
            llvm::AAResults *aa = alias.request(*fnNoConst);
            if(aa->alias(storeLoc, selfLoc) > llvm::AliasResult::MayAlias) {
                return true;
            }
        }

        if(auto call = llvm::dyn_cast<llvm::CallInst>(&llvmIns)) {
            auto fnc = call->getCalledFunction();
            auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
            vanguard::Function* fncV = llvmToVanguard.translateFunction(fn);
            //Can only store contract variables
            if(InkToLLVM::isLazyStore(*fncV)) {
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
            throw runtime_error("Expected there to be at least one input to " + fn->getName().str());
        }

        auto selfArg = InkToLLVM::getSelfRef(*blkFn, *fnV);
        llvm::MemoryLocation selfLoc = llvm::MemoryLocation::getAfter(selfArg);

        if(InkToLLVM::isMemoryRead(ins)) {
            llvm::MemoryLocation readLoc = InkToLLVM::getReadLocation(ins);

            llvm::Function* fnNoConst = const_cast<llvm::Function*>(fn); // how I fixed it
            llvm::AAResults *aa = alias.request(*fnNoConst); // otherwise  alias.request(*fn), which throws error
            if(aa->alias(readLoc, selfLoc) > llvm::AliasResult::MayAlias) {
                return true;
            }
        }

        if(auto call = llvm::dyn_cast<llvm::CallInst>(&llvmIns)) {
            auto fn = call->getCalledFunction();
            auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
            vanguard::Function* fnV = llvmToVanguard.translateFunction(fn);

            //Can only store contract variables
            if(InkToLLVM::isLazyGet(*fnV)) {
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

            if(InkToLLVM::isMsgSender(*fnV)) {
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

            if(InkToLLVM::isMsgValue(*fnV)) {
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

            if(InkToLLVM::isSelfDestruct(*fnV)) {
                return true;
            }
        }

        return false;
    }
}