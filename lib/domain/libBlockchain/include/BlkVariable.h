//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKVARIABLE_H
#define LIBBLOCKCHAIN_BLKVARIABLE_H

#include <string>
//#include <llvm/IR/Instruction.h>
#include "../../../program/Instruction.h"
#include "../../../program/Value.h"
#include "BlkType.h"

using namespace std;

namespace blockchain {
class BlkVariable : public BlkNode, public vanguard::Value {
    public:
        BlkVariable(BlockchainToLLVM *blk2llvm, string &name, BlkType *type);
        ~BlkVariable();

        static inline bool classof(const BlkVariable &) { return true; }
        static inline bool classof(const BlkVariable *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == VARIABLE) { return true; }
            return false;
        }

        const BlkType &varType() const;
        bool writtenBy(vanguard::Instruction &ins) const;
        bool readBy(vanguard::Instruction &ins) const;
    private:
        BlkType *varTy;
    };
}



#endif //LIBBLOCKCHAIN_BLKVARIABLE_H
