//
// Created by Kostas Ferles on 10/21/22.
//

#ifndef VANGUARD_SOLIDITYFACTORY_H
#define VANGUARD_SOLIDITYFACTORY_H

#include "domain/libBlockchain/langs/LanguageFactory.h"

namespace vanguard {

    class SolidityFactory : public LanguageFactory {
    public:
        inline explicit SolidityFactory(BlockchainDomain::Factory &factory) : LanguageFactory(factory) {}

        BlockchainDomain::Type *createBasicType(rapidjson::Value &val, const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string name) override;

        Visibility toVisibility(const std::string& visStr) override;

        Mutability toMutability(const std::string& mutStr) override;
    };

}


#endif //VANGUARD_SOLIDITYFACTORY_H
