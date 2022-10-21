//
// Created by Kostas Ferles on 10/21/22.
//

#include "NearFactory.h"

namespace vanguard {

    BlockchainDomain::Type* NearFactory::createBasicType(const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string name) {
        // TODO: Implement this.
        return nullptr;
    }

    Visibility NearFactory::toVisibility(const std::string &visStr) {
        if(visStr == "public") { return PUBLIC; }
        if(visStr == "private") { return PRIVATE; }

        throw std::runtime_error("Unknown visibility " + visStr);
    }

    Mutability NearFactory::toMutability(const std::string &mutStr) {
        // TODO: make sure these are consistent with NEAR jargon
        if(mutStr == "payable") { return PAYABLE; }
        if(mutStr == "nonpayable") { return NONPAYABLE; }

        throw std::runtime_error("Unknown mutability " + mutStr);
    }

}
