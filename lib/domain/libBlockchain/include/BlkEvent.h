//
// Created by Jon Stephens on 4/14/22.
//

#include <string>
#include "BlkNode.h"
#include "BlkVariable.h"

#ifndef LIBBLOCKCHAIN_BLKEVENT_H
#define LIBBLOCKCHAIN_BLKEVENT_H

namespace blockchain {
    class BlkEvent : public BlkNode {
    public:
        BlkEvent(BlockchainModel *blk2llvm, std::string &name, std::vector<BlkVariable *> params);
        ~BlkEvent();

        static inline bool classof(const BlkEvent &) { return true; }
        static inline bool classof(const BlkEvent *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == EVENT) { return true; }
            return false;
        }

        const std::vector<BlkVariable *> &parameters() const;
        bool emits(vanguard::Instruction &ins) const;

    private:
        std::vector<BlkVariable *> eventParams;
    };
}


#endif //LIBBLOCKCHAIN_BLKEVENT_H
