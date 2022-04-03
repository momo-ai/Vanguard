//
// Created by Jon Stephens on 3/30/22.
//

#ifndef VANGUARD_EXAMPLESOURCE_H
#define VANGUARD_EXAMPLESOURCE_H

#include "../../FunctionTaintSource.h"

namespace flashloan {
    class BalanceOfSource : public vanguard::FunctionTaintSource {
        bool isSource(const llvm::Function &fn) override;
        std::vector<std::pair<vanguard::FunctionLocation, vanguard::Val *>> sourceValues(const llvm::Function &fn) override;
    };
}



#endif //VANGUARD_EXAMPLESOURCE_H
