//
// Created by Jon Stephens on 3/20/22.
//

#include "domain/libBlockchain/include/Blockchain.h"
#include "domain/libBlockchain/include/solidity/Solidity.h"
#include "domain/libBlockchain/include/BlockchainModel.h"
#include "domain/libBlockchain/include/solidity/SolangModel.h"
#include <llvm/IR/Instructions.h>

#include <utility>


namespace blockchain {
    Solidity::Solidity(BlockchainModel *blk2llvm, std::string &c, std::string &v, std::vector<BlkContract *> contracts)
        : Blockchain(SOLIDITY, blk2llvm, c, v, std::move(contracts)) {}


    bool Solidity::allowsReentrancy() const {
        return true;
    }

    bool Solidity::writesStorage(vanguard::Instruction &ins) {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if (auto call = llvm::dyn_cast<llvm::CallInst>(&llvmIns)) {
            auto fn = call->getCalledFunction();
            auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
            vanguard::Function* fnV = llvmToVanguard.translateFunction(fn);

            return SolangModel::writesStorage(*fnV);

            //assume assigns goes through setter
            /*auto fn = call->getCalledFunction();
            if(fn->hasName() && fn->getName().str() == "storageStore") {
                return true;
            }*/
        }

        return false;
    }

    bool Solidity::readsStorage(vanguard::Instruction &ins) {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if (auto call = llvm::dyn_cast<llvm::CallInst>(&llvmIns)) {
            auto fn = call->getCalledFunction();
            auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
            vanguard::Function* fnV = llvmToVanguard.translateFunction(fn);

            return SolangModel::readsStorage(*fnV);

            //assume assigns goes through setter
            /*auto fn = call->getCalledFunction();
            if(fn->hasName() && fn->getName().str() == "storageStore") {
                return true;
            }*/
        }

        return false;
    }



    bool Solidity::getsSender(vanguard::Instruction &ins) const {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(auto call = llvm::dyn_cast<llvm::CallInst>(&llvmIns)) {
            auto fn = call->getCalledFunction();
            if(fn->hasName() && fn->getName().str() == "getCaller") {
                return true;
            }
        }

        return false;
    }

    bool Solidity::getsValue(vanguard::Instruction &ins) const {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(auto call = llvm::dyn_cast<llvm::CallInst>(&llvmIns)) {
            auto fn = call->getCalledFunction();
            if(fn->hasName() && fn->getName().str() == "getCallValue") {
                return true;
            }
        }

        return false;
    }

    bool Solidity::isSelfDestruct(vanguard::Instruction &ins) const {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(auto call = llvm::dyn_cast<llvm::CallInst>(&llvmIns)) {
            auto fn = call->getCalledFunction();
            if(fn->hasName() && fn->getName().str() == "selfDestruct") {
                return true;
            }
        }

        return false;
    }
}