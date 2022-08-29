//
// Created by Jon Stephens on 4/14/22.
//

#include "../include/BlkEvent.h"

using namespace std;

namespace blockchain {
    BlkEvent::BlkEvent(BlockchainModel *blk2llvm, std::string &name, vector<BlkVariable *> params) : eventParams(std::move(params)), BlkNode(EVENT, blk2llvm, name) {
        registerParent(eventParams);
    }

    BlkEvent::~BlkEvent() {
        deleter(eventParams);
    }

    const vector<BlkVariable *> &BlkEvent::parameters() const {
        return eventParams;
    }

    bool BlkEvent::emits(vanguard::Instruction &ins) const {
        return false;
    }
}