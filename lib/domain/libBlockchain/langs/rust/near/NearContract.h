//
// Created by Kostas Ferles on 10/21/22.
//

#ifndef VANGUARD_NEARCONTRACT_H
#define VANGUARD_NEARCONTRACT_H

#include <utility>
#include "program/Type.h"
#include "domain/libBlockchain/Type.h"

#include "domain/libBlockchain/Contract.h"
#include "domain/Domains.h"

namespace vanguard {

    class NearContract : public BlockchainDomain::Contract {
    public:
        inline NearContract(BlockchainModel<BlockchainDomain> &model, std::string name,
                            std::vector<BlockchainDomain::Function *> fns,
                            std::vector<vanguard::Variable<BlockchainDomain> *> vars,
                            bool external)
                            : BlockchainDomain::Contract(model, std::move(name), std::move(fns), std::move(vars)), external(external) {

        }

        inline bool isExternal() {
            return external;
        }

    private:
        bool external = false;
    };

}

#endif //VANGUARD_NEARCONTRACT_H
