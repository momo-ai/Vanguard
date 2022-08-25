//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkVariable.h"
#include "../include/BlockchainToLLVM.h"


namespace blockchain {
    // TODO: Confirm with Jon that this is all that is needed to set
    BlkVariable::BlkVariable(BlockchainToLLVM *blk2llvm, string &name, BlkType *type) : BlkNode(VARIABLE, blk2llvm, name), vanguard::Value(vanguard::BLKVARIABLE) {
        type->parent(this);
        // or do we do type->getType()
    }

    BlkVariable::~BlkVariable() {
        delete varTy;
    }

    const BlkType &BlkVariable::varType() const {
        return *varTy;
    }

    bool BlkVariable::writtenBy(vanguard::Instruction &ins) const {
        return blkTollvm->writesVariable(*this, ins);
    }
    bool BlkVariable::readBy(vanguard::Instruction &ins) const {
        return blkTollvm->readsVariable(*this, ins);
    }
}