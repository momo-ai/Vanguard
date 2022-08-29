//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkEnum.h"

using namespace std;

namespace blockchain {
    BlkEnum::BlkEnum(BlockchainModel *blk2llvm, string &name, map<std::string, int> vals) : values(std::move(vals)), BlkStorage(ENUM, blk2llvm, name) {
    }

    BlkEnum::~BlkEnum() {
    }
}