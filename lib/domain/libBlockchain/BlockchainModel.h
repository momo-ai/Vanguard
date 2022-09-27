//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLOCKCHAINTOLLVM_H
#define LIBBLOCKCHAIN_BLOCKCHAINTOLLVM_H

#include "Blockchain.h"
#include "CallResolver.h"


namespace vanguard {
    template<typename Domain>
    class BlockchainModel {
        public:
            virtual ~BlockchainModel() = default;
            virtual bool isImplementation(std::string contract, const typename Domain::Function &blockchainFn, const llvm::Function &llvmFn) const = 0;
            virtual bool isAnyLowLevelCall(CallIns<Domain> &call) const = 0;
            virtual bool isLowLevelCall(CallIns<Domain> &call) const = 0;
            virtual bool isLowLevelStaticCall(CallIns<Domain> &call) const = 0;
            virtual bool isLowLevelDelegateCall(CallIns<Domain> &call) const = 0;
            virtual bool writesStorage(typename Domain::Instruction &ins) const = 0;
            virtual bool readsStorage(typename Domain::Instruction &ins) const = 0;
            virtual CallResolver<Domain> *callResolver() const = 0;
            virtual bool isExternalCall(CallIns<Domain> &call) const = 0;
            //virtual bool isDelegateCall(const llvm::Function &llvmFn) = 0;
            //virtual bool isAnyExternalCall(vanguard::Function &llvmFn) const = 0;
            //virtual bool isCall(vanguard::Function &llvmFn) const = 0;
            //virtual bool isStaticCall(vanguard::Function &llvmFn) const = 0;
            //virtual bool isDelegateCall(vanguard::Function &llvmFn) const = 0;

            //virtual bool writesVariable(const BlkVariable &var, vanguard::Instruction &ins) const = 0;
            //virtual bool readsVariable(const BlkVariable &var, vanguard::Instruction &ins) const = 0;
        private:
    };
}



#endif //LIBBLOCKCHAIN_BLOCKCHAINTOLLVM_H
