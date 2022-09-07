//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLOCKCHAIN_H
#define LIBBLOCKCHAIN_BLOCKCHAIN_H

//#include "llvm/IR/Function.h"
#include "../../../program/Function.h"
//#include "llvm/IR/Instruction.h"
#include "../../../program/Instruction.h"
#include "BlkContract.h"
#include "../../../detectors/AAWrapper.h"
#include "../../Domain.h"
#include <vector>
#include "../../../program/LLVMtoVanguard.h"

using namespace std;

namespace blockchain {
class Blockchain : public BlkNode, public vanguard::Domain {
    public:
        // Methods inherited from BlkNode
        Blockchain(NodeType t, BlockchainToLLVM *blk2llvm, string &name, string &version, vector<BlkContract *> *contracts) : BlkNode(t, blk2llvm, name), srcVersion(version), allContracts(contracts) {}
        ~Blockchain();

        static inline bool classof(const Blockchain &) { return true; }
        static inline bool classof(const Blockchain *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() >= BLOCKCHAIN_BEGIN && node.type() <= BLOCKCHAIN_END) { return true; }
            return false;
        }

        static std::string getThing();

        virtual bool allowsReentrancy() const = 0;
        virtual bool getsSender(vanguard::Instruction &ins) const = 0;
        virtual bool getsValue(vanguard::Instruction &ins) const = 0;
        virtual bool isSelfDestruct(vanguard::Instruction &ins) const = 0;
        virtual bool isContractFunction(vanguard::Function &fn) const;
        virtual const vector<BlkContract *> &contracts() const;
        virtual const BlkContract *findDeclaringContract(vanguard::Function &fn) const;
        virtual const BlkFunction *findFunction(vanguard::Function &fn) const;
        virtual bool isAnyExternalCall(vanguard::Function &fn) const;
        virtual bool isCall(vanguard::Function &fn) const;
        virtual bool isStaticCall(vanguard::Function &fn) const;
        virtual bool isDelegateCall(vanguard::Function &fn) const;

        // overridden from Domain class, implementation begins L83 Blockchain.cpp
        virtual bool resolvesCalls() override;
        virtual std::list<vanguard::CallEdge*> getCallees(vanguard::Context context, vanguard::CallExpr &ins) override;
        virtual bool hasAdditionalStorage() override;
//        virtual std::list<vanguard::Value*> getAdditionalStorage() override;
//        virtual std::list<vanguard::Value*> getStorageReads(vanguard::Instruction& ins) override;
//        virtual std::list<vanguard::Value*> getStorageWrites(vanguard::Instruction& ins) override;

    protected:
        string srcVersion;
        vector<BlkContract *> *allContracts;
    };
}

#endif //LIBBLOCKCHAIN_BLOCKCHAIN_H
