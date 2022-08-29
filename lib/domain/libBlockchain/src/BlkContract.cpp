//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkContract.h"
#include "../include/BlockchainModel.h"

namespace blockchain {
    BlkContract::BlkContract(BlockchainModel *blk2llvm, std::string &name, std::vector<BlkFunction *> fns, std::vector<BlkVariable *> vars, std::vector<BlkUserType *> inherits,
                             std::vector<BlkEnum *> enums, std::vector<BlkStruct *> structs, std::vector<BlkEvent *> events) : Container<BlkFunction>(std::move(fns)), BlkStorage(CONTRACT, blk2llvm, name) {
        registerParent(contained);
        contractVars = vars;
        registerParent(contractVars);
        contractInherits = inherits;
        registerParent(contractInherits);
        contractEnums = enums;
        registerParent(contractEnums);
        contractStructs = structs;
        registerParent(contractStructs);
        contractEvents = events;
        registerParent(contractEvents);
    }

    BlkContract::~BlkContract() {
        deleter(contractInherits);
        deleter(contractEvents);
        deleter(contractEnums);
        deleter(contractStructs);
        deleter(contractVars);
        deleter(contained);
    }

    std::vector<BlkContract *> BlkContract::inherits() const {
        std::vector<BlkContract *> inherits;

        for(auto inherit : contractInherits) {
            if(auto inheritFrom = llvm::dyn_cast<BlkContract>(inherit)) {
                inherits.push_back(inheritFrom);
            }
            else {
                throw std::runtime_error("Must inherit from contracts");
            }
        }

        return inherits;
    }

    const std::vector<BlkVariable *> &BlkContract::variables() const {
        return contractVars;
    }

    bool BlkContract::isContractFunction(vanguard::Function &fn) const {
        return findFunction(fn) != nullptr;
    }

    const BlkFunction *BlkContract::findFunction(vanguard::Function &fn) const {
        for(auto blkFn : contained) {
            if(blkFn->isTranslation(fn)) {
                return blkFn;
            }
        }

        return nullptr;
    }

    const std::vector<BlkFunction *> &BlkContract::functions() const {
        return contained;
    }
}