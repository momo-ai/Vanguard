//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKSTRUCT_H
#define LIBBLOCKCHAIN_BLKSTRUCT_H

#include <string>
#include <vector>
#include "BlkVariable.h"
#include "BlkVariable.h"
#include "BlkStorage.h"

namespace blockchain {
    class BlkStruct : public BlkStorage {
    public:
        BlkStruct(BlockchainModel *blk2llvm, std::string &name, std::vector<BlkVariable *> fields);
        ~BlkStruct();

        static inline bool classof(const BlkStruct &) { return true; }
        static inline bool classof(const BlkStruct *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == STRUCT) { return true; }
            return false;
        }
    private:
        std::vector<BlkVariable *> structFields;
    };
}

#endif //LIBBLOCKCHAIN_BLKSTRUCT_H
