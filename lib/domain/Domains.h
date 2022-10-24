//
// Created by Kostas Ferles on 10/21/22.
//

#ifndef VANGUARD_DOMAINS_H
#define VANGUARD_DOMAINS_H

#include <domain/libBlockchain/Blockchain.h>

namespace vanguard {

    class BlockchainDomain : public Blockchain<Base<BlockchainDomain>, BlockchainDomain> {

    };

    class LLVMDomain : public Base<LLVMDomain> {

    };
}

#endif //VANGUARD_DOMAINS_H
