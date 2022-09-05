//
// Created by Jon Stephens on 4/10/22.
//

#ifndef LIBBLOCKCHAIN_INKTOLLVM_H
#define LIBBLOCKCHAIN_INKTOLLVM_H

#include "domain/libBlockchain/include/BlockchainModel.h"
#include "analysis/alias/AAWrapper.h"
#include "llvm/Analysis/MemoryLocation.h"
//#include "llvm/IR/Function.h"
#include "program/LLVMFactory.h"


namespace blockchain {
    class InkModel : public BlockchainModel {
    public:
        explicit InkModel(vanguard::AAWrapper &alias);
        bool isTranslation(const BlkFunction &blockchainFn, vanguard::Function &fn) const override;
        bool isAnyExternalCall(vanguard::Function &fn) const override;
        bool isCall(vanguard::Function &fn) const override;
        bool isStaticCall(vanguard::Function &fn) const override;
        bool isDelegateCall(vanguard::Function &fn) const override;
        bool writesVariable(const BlkVariable &var, vanguard::Instruction &ins) const override;
        bool readsVariable(const BlkVariable &var, vanguard::Instruction &ins) const override;
        static bool isLazyGet(vanguard::Function &fn);
        static bool isLazyStore(vanguard::Function &fn);
        static bool isMsgSender(vanguard::Function &fn);
        static bool isMsgValue(vanguard::Function &fn);
        static bool isSelfDestruct(vanguard::Function &fn);
        static bool isMemoryStore(vanguard::Instruction &ins);
        static bool isMemoryRead(vanguard::Instruction &ins);
        static llvm::MemoryLocation getStoreLocation(vanguard::Instruction &ins);
        static llvm::MemoryLocation getReadLocation(vanguard::Instruction &ins);
        static llvm::Value *getSelfRef(const BlkFunction &blkFn, vanguard::Function &fn);

    private:
        vanguard::AAWrapper &alias;

        static bool isConstructorClosure(const BlkFunction &blockchainFn, vanguard::Function &fn);
    };
}


#endif //LIBBLOCKCHAIN_INKTOLLVM_H
