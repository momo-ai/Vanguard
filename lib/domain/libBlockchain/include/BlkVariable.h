//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKVARIABLE_H
#define LIBBLOCKCHAIN_BLKVARIABLE_H

#include <string>
//#include <llvm/IR/Instruction.h>
#include "../../../program/Value.h"
#include "BlkType.h"

namespace blockchain {
class BlkVariable : public BlkNode, public vanguard::Variable {
    public:
        BlkVariable(BlockchainModel *blk2llvm, std::string &name, BlkType *type);
        ~BlkVariable();

        static inline bool classof(const BlkVariable &) { return true; }
        static inline bool classof(const BlkVariable *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == VARIABLE) { return true; }
            return false;
        }


        bool hasName() const override;
        std::string name() const override;
        const BlkType &varType() const;
        vanguard::Type* type() const override;
        bool writtenBy(vanguard::Instruction &ins) const;
        bool readBy(vanguard::Instruction &ins) const;
        void accept(vanguard::ValueClassVisitor &v) const override;
    private:
        BlkType *varTy;
    };
}



#endif //LIBBLOCKCHAIN_BLKVARIABLE_H
