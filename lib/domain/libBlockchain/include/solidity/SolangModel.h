//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_SOLANGTOLLVM_H
#define LIBBLOCKCHAIN_SOLANGTOLLVM_H

#include "domain/libBlockchain/include/BlockchainModel.h"
//#include "llvm/IR/Function.h"
#include "program/Function.cpp"

namespace blockchain {
    class SolangModel : public BlockchainModel {
    public:
        bool isTranslation(const BlkFunction &blockchainFn, vanguard::Function &fn) const override;
        //bool isExternalCall(const llvm::Function &llvmFn) override;
        //bool isDelegateCall(const llvm::Function &llvmFn) override;
        bool isAnyExternalCall(vanguard::Function &fn) const override;
        bool isCall(vanguard::Function &fn) const override;
        bool isStaticCall(vanguard::Function &fn) const override;
        bool isDelegateCall(vanguard::Function &fn) const override;
        bool writesVariable(const BlkVariable &var, vanguard::Instruction &ins) const override;
        bool readsVariable(const BlkVariable &var, vanguard::Instruction &ins) const override;

        static bool writesStorage(vanguard::Function &fn);
        static bool readsStorage(vanguard::Function &fn);
    private:
    };
}



#endif //LIBBLOCKCHAIN_SOLANGTOLLVM_H
