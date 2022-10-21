//
// Created by Kostas Ferles on 10/21/22.
//

#include "SolidityFactory.h"

namespace vanguard {

    BlockchainDomain::Type* SolidityFactory::createBasicType(rapidjson::Value &val, const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string name) {
        // TODO: Implement this.
        return nullptr;
    }

    Visibility SolidityFactory::toVisibility(const std::string &visStr) {
        if(visStr == "external") { return EXTERNAL; }
        if(visStr == "public") { return PUBLIC; }
        if(visStr == "internal") { return INTERNAL; }
        if(visStr == "private") { return PRIVATE; }

        throw std::runtime_error("Unknown visibility " + visStr);
    }

    Mutability SolidityFactory::toMutability(const std::string &mutStr) {
        if(mutStr == "pure") { return PURE; }
        if(mutStr == "view") { return VIEW; }
        if(mutStr == "payable") { return PAYABLE; }
        if(mutStr == "nonpayable") { return NONPAYABLE; }

        throw std::runtime_error("Unknown mutability " + mutStr);
    }

}