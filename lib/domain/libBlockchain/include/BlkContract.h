//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKCONTRACT_H
#define LIBBLOCKCHAIN_BLKCONTRACT_H

//#include "llvm/IR/Function.h"
#include <program/Function.cpp>
#include <domain/Container.h>
#include "BlkEnum.h"
#include "BlkStruct.h"
#include "BlkVariable.h"
#include "BlkFunction.h"
#include "BlkUserType.h"
#include <vector>
#include "BlkNode.h"
#include "BlkEvent.h"

namespace blockchain {
    class BlkContract : public BlkStorage, public vanguard::Container<BlkFunction> {
    public:
        BlkContract(BlockchainModel *blk2llvm, std::string &name, std::vector<BlkFunction *> fns, std::vector<BlkVariable *> vars, std::vector<BlkUserType *> inherits,
                    std::vector<BlkEnum *> enums, std::vector<BlkStruct *> structs, std::vector<BlkEvent *> events);
        ~BlkContract();

        static inline bool classof(const BlkContract &) { return true; }
        static inline bool classof(const BlkContract *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == CONTRACT) { return true; }
            return false;
        }
        bool isContractFunction(vanguard::Function &fn) const;
        const BlkFunction *findFunction(vanguard::Function &fn) const;
        const std::vector<BlkFunction *> &functions() const;
        const std::vector<BlkVariable *> &variables() const;
        std::vector<BlkContract *> inherits() const;
    private:
        std::vector<BlkUserType *> contractInherits;
        std::vector<BlkEvent *> contractEvents;
        std::vector<BlkEnum *> contractEnums;
        std::vector<BlkStruct *> contractStructs;
        std::vector<BlkVariable *> contractVars;
    };
}



#endif //LIBBLOCKCHAIN_BLKCONTRACT_H
