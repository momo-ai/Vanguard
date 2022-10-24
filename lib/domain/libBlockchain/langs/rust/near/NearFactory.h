//
// Created by Kostas Ferles on 10/21/22.
//

#ifndef VANGUARD_NEARFACTORY_H
#define VANGUARD_NEARFACTORY_H


#include "domain/libBlockchain/langs/LanguageFactory.h"

namespace vanguard {

    class NearFactory : public LanguageFactory {
    public:

        inline explicit NearFactory(BlockchainDomain::Factory &factory) : LanguageFactory(factory) { }

        BlockchainDomain::Contract *createContract(rapidjson::Value &val, const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string& name,
                                                   std::vector<BlockchainDomain::Function *>& fns, std::vector<Variable<BlockchainDomain> *>& vars) override;

        BlockchainDomain::Type *createBasicType(rapidjson::Value &val, const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string name) override;

        Visibility toVisibility(const std::string& visStr) override;

        Mutability toMutability(const std::string& mutStr) override;

    };

}


#endif //VANGUARD_NEARFACTORY_H
