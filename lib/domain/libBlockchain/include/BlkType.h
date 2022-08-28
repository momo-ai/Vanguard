//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLKTYPE_H
#define LIBBLOCKCHAIN_BLKTYPE_H

#include "../../../program/Type.h"
#include "BlkNode.h"

namespace blockchain {
    class BlkTypeVisitor;
    class BlkType : public BlkNode, public vanguard::Type {
    public:
        explicit BlkType(NodeType t, BlockchainToLLVM *blk2llvm, std::string &name) : BlkNode(t, blk2llvm, name) {}
        virtual ~BlkType() = default;

        static inline bool classof(const BlkType &) { return true; }
        static inline bool classof(const BlkType *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() >= TYPE_BEGIN && node.type() <= TYPE_END) { return true; }
            return false;
        }

        std::string name() const override {
            return blkName();
        }

        virtual void accept(BlkTypeVisitor &v) const = 0;
    };
}



#endif //LIBBLOCKCHAIN_BLKTYPE_H
