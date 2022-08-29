//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_SOLIDITY_H
#define LIBBLOCKCHAIN_SOLIDITY_H


#include "domain/libBlockchain/include/Blockchain.h"

namespace blockchain {
    class Solidity : public Blockchain {
    public:
        Solidity(BlockchainModel *blk2llvm, std::string &c, std::string &v, std::vector<BlkContract *> contracts);

        static inline bool classof(const Solidity &) { return true; }
        static inline bool classof(const Solidity *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == SOLIDITY) { return true; }
            return false;
        }

        bool allowsReentrancy() const override;
        bool writesStorage(vanguard::Instruction &ins) override;
        bool readsStorage(vanguard::Instruction &ins) override;
        bool getsSender(vanguard::Instruction &ins) const override;
        bool getsValue(vanguard::Instruction &ins) const override;
        bool isSelfDestruct(vanguard::Instruction &ins) const override;
    };
}

#endif //LIBBLOCKCHAIN_SOLIDITY_H
