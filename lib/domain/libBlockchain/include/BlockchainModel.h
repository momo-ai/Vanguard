//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLOCKCHAINTOLLVM_H
#define LIBBLOCKCHAIN_BLOCKCHAINTOLLVM_H

#include "BlkFunction.h"


namespace blockchain {
    class BlockchainModel {
        public:
            virtual ~BlockchainModel() = default;
            virtual bool isTranslation(const BlkFunction &blockchainFn, vanguard::Function &llvmFn) const = 0;
            //virtual bool isExternalCall(const llvm::Function &llvmFn) = 0;
            //virtual bool isDelegateCall(const llvm::Function &llvmFn) = 0;
            virtual bool isAnyExternalCall(vanguard::Function &llvmFn) const = 0;
            virtual bool isCall(vanguard::Function &llvmFn) const = 0;
            virtual bool isStaticCall(vanguard::Function &llvmFn) const = 0;
            virtual bool isDelegateCall(vanguard::Function &llvmFn) const = 0;

            virtual bool writesVariable(const BlkVariable &var, vanguard::Instruction &ins) const = 0;
            virtual bool readsVariable(const BlkVariable &var, vanguard::Instruction &ins) const = 0;
        private:
    };
}



#endif //LIBBLOCKCHAIN_BLOCKCHAINTOLLVM_H
