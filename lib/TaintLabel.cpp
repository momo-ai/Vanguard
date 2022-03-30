//
// Created by Jon Stephens on 3/29/22.
//

#include "TaintLabel.h"
#include <exception>

namespace vanguard {
    TaintLabel::TaintLabel(uint id) : tid(id) {
        if(id >= 64) {
            throw std::out_of_range("Can only have up to 64 taint labels per labelStore");
        }
    }

    uint TaintLabel::id() const {
        return tid;
    }

    uint64_t TaintLabel::taintMask() const {
        return 0x1 << tid;
    }
}