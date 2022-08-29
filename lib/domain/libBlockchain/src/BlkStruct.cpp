//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkStruct.h"

#include <utility>

using namespace std;

namespace blockchain {
    BlkStruct::BlkStruct(BlockchainModel *blk2llvm, string &name, vector<BlkVariable *> fields) : structFields(std::move(fields)), BlkStorage (STRUCT, blk2llvm, name) {
        registerParent(structFields);
    }

    BlkStruct::~BlkStruct() {
        deleter(structFields);
    }
}