//
// Created by Jon Stephens on 4/10/22.
//

#ifndef LIBBLOCKCHAIN_INK_H
#define LIBBLOCKCHAIN_INK_H

#include "domain/libBlockchain/include/Blockchain.h"

namespace blockchain {
    class Ink : public Blockchain {
    public:
        Ink(BlockchainModel *blk2llvm, std::string &c, std::string &v, std::vector<BlkContract *> contracts, vanguard::AAWrapper &alias);

        static inline bool classof(const Ink &) { return true; }
        static inline bool classof(const Ink *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == INK) { return true; }
            return false;
        }

        bool allowsReentrancy() const override;
        bool readsStorage(vanguard::Instruction &ins) override;
        bool writesStorage(vanguard::Instruction &ins) override;
        bool getsSender(vanguard::Instruction &ins) const override;
        bool getsValue(vanguard::Instruction &ins) const override;
        bool isSelfDestruct(vanguard::Instruction &ins) const override;
    private:
        vanguard::AAWrapper &alias;
    };
}




#endif //LIBBLOCKCHAIN_INK_H
