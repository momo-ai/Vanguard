//
// Created by Kostas Ferles on 8/29/22.
//

#ifndef VANGUARD_NEARTOLLVM_H
#define VANGUARD_NEARTOLLVM_H

#include "BlockchainToLLVM.h"
#include "Near.h"
#include "../../../detectors/AAWrapper.h"

namespace blockchain {
    class NearToLLVM : public BlockchainToLLVM {
    public:
        explicit NearToLLVM(vanguard::AAWrapper &alias);

        bool isTranslation(const BlkFunction &blockchainFn, vanguard::Function &fun) const override;

        bool isAnyExternalCall(vanguard::Function &llvmFn) const override;

        bool isCall(vanguard::Function &llvmFn) const override;

        bool isStaticCall(vanguard::Function &llvmFn) const override;

        bool isDelegateCall(vanguard::Function &llvmFn) const override;

        bool writesVariable(const BlkVariable &var, vanguard::Instruction &ins) const override;

        bool readsVariable(const BlkVariable &var, vanguard::Instruction &ins) const override;

        void setNear(blockchain::Near *near);

    private:
        vanguard::AAWrapper &alias;

        blockchain::Near *near;
    };
}

#endif //VANGUARD_NEARTOLLVM_H
