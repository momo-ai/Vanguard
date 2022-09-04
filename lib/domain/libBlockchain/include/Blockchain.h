//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLOCKCHAIN_H
#define LIBBLOCKCHAIN_BLOCKCHAIN_H

#include <program/Function.cpp>
#include <program/Instruction.h>
#include <program/LLVMFactory.h>
#include <analysis/alias/AAWrapper.h>
#include <domain/Domain.h>
#include <domain/Container.h>
#include "BlkContract.h"
#include <utility>
#include <vector>

namespace blockchain {
class Blockchain : public BlkNode, public vanguard::Domain, public vanguard::Container<BlkContract> {
    public:
        // Methods inherited from BlkNode
        Blockchain(NodeType t, BlockchainModel *blk2llvm, std::string &name, std::string &version, std::vector<BlkContract *> contracts)
            : BlkNode(t, blk2llvm, name), vanguard::Container<BlkContract>(std::move(contracts)), srcVersion(version) {};
        ~Blockchain();

        static inline bool classof(const Blockchain &) { return true; }
        static inline bool classof(const Blockchain *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() >= BLOCKCHAIN_BEGIN && node.type() <= BLOCKCHAIN_END) { return true; }
            return false;
        }

        virtual bool allowsReentrancy() const = 0;
        virtual bool getsSender(vanguard::Instruction &ins) const = 0;
        virtual bool getsValue(vanguard::Instruction &ins) const = 0;
        virtual bool isSelfDestruct(vanguard::Instruction &ins) const = 0;
        virtual bool isContractFunction(vanguard::Function &fn) const;
        virtual const std::vector<BlkContract *> &contracts() const;
        virtual const BlkContract *findDeclaringContract(vanguard::Function &fn) const;
        virtual const BlkFunction *findFunction(vanguard::Function &fn) const;
        virtual bool isAnyExternalCall(vanguard::Function &fn) const;
        virtual bool isCall(vanguard::Function &fn) const;
        virtual bool isStaticCall(vanguard::Function &fn) const;
        virtual bool isDelegateCall(vanguard::Function &fn) const;

        // overridden from Domain class, implementation begins L83 Blockchain.cpp
        bool resolvesCalls() override;
        std::list<vanguard::CallEdge*> getCallees(vanguard::Context context, vanguard::CallExpr &ins) override;
        bool hasAdditionalStorage() override;
        std::list<vanguard::Value*> getAdditionalStorage() override;
        std::list<vanguard::Value*> getStorageReads(vanguard::Instruction& ins) override;
        std::list<vanguard::Value*> getStorageWrites(vanguard::Instruction& ins) override;

    protected:
        std::string srcVersion;
    };
}

#endif //LIBBLOCKCHAIN_BLOCKCHAIN_H
