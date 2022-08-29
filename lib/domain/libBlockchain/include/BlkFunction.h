//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKFUNCTION_H
#define LIBBLOCKCHAIN_BLKFUNCTION_H

//#include "llvm/IR/Function.h"
#include "../../../program/Function.h"
#include <string>
#include <vector>
#include "BlkVariable.h"

namespace blockchain {
    enum Mutability {
        PURE,
        VIEW,
        PAYABLE,
        NONPAYABLE
    };

    enum Visibility {
        EXTERNAL,
        PUBLIC,
        INTERNAL,
        PRIVATE,
        DEFAULT
    };

    class BlkFunction : public BlkNode {
    public:
        BlkFunction(BlockchainModel *blk2llvm, std::string &name, bool isCnstr, Visibility visibility, Mutability mutability, std::vector<BlkVariable *> params, std::vector<BlkVariable *> rets, std::vector<std::string> mods);
        ~BlkFunction();

        static inline bool classof(const BlkFunction &) { return true; }
        static inline bool classof(const BlkFunction *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == FUNCTION) { return true; }
            return false;
        }

        void setSelector(std::string selector);
        std::string selector();
        const std::vector<std::string> &modifiers() const;
        const std::vector<BlkVariable *> &parameters() const;
        bool isTranslation(vanguard::Function &fn) const;
        bool isConstructor() const;
        Visibility visibility() const;
        Mutability mutability() const;

        static Mutability toMutability(const std::string& mutStr);
        static Visibility toVisibility(const std::string& visStr);
    private:
        bool fnIsConstructor;
        std::vector<BlkVariable *> fnParams;
        std::vector<BlkVariable *> fnReturns;
        std::vector<std::string> fnMods;
        Visibility visible;
        Mutability mut;
        std::string fnSelector;
    };
}



#endif //LIBBLOCKCHAIN_BLKFUNCTION_H
