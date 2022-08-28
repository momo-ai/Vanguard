//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkVariable.h"
#include "../include/BlockchainToLLVM.h"


namespace blockchain {
    // TODO: Confirm with Jon that this is all that is needed to set
    BlkVariable::BlkVariable(BlockchainToLLVM *blk2llvm, string &name, BlkType *type) : BlkNode(VARIABLE, blk2llvm, name), vanguard::Variable(vanguard::BLKVARIABLE), varTy(type) {
        type->parent(this);
        // or do we do type->getType()
    }

    BlkVariable::~BlkVariable() {
        delete varTy;
    }

    const BlkType &BlkVariable::varType() const {
        return *varTy;
    }

    vanguard::Type* BlkVariable::type() const {
        return varTy;
    }

    bool BlkVariable::hasName() const {
        return true;
    }

    std::string BlkVariable::name() const {
        return blkName();
    }

    bool BlkVariable::writtenBy(vanguard::Instruction &ins) const {
        return blkTollvm->writesVariable(*this, ins);
    }

    bool BlkVariable::readBy(vanguard::Instruction &ins) const {
        return blkTollvm->readsVariable(*this, ins);
    }

    void BlkVariable::accept(vanguard::ValueClassVisitor &v) const {
        return v.visit(*this);
    }
}