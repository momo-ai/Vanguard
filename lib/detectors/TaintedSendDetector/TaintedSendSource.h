//
// Created by Ben Mariano on 4/3/22.
//

#ifndef VANGUARD_TAINTSENDANALYSIS_H
#define VANGUARD_TAINTSENDANALYSIS_H

#include "../../FunctionTaintSource.h"

using namespace vanguard;

namespace TaintedSend {
    class TaintedSendSource : public FunctionTaintSource {
        bool isSource(const llvm::Function &fn) override;
        std::vector<std::pair<FunctionLocation, Val *>> sourceValues(const llvm::Function &fn) override;
    };
}



#endif //VANGUARD_TAINTSENDANALYSIS_H
