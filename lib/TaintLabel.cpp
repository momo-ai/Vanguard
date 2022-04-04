//
// Created by Jon Stephens on 3/29/22.
//

#include "TaintLabel.h"
#include <exception>
#include "TaintSummary.h"

namespace vanguard {
    TaintLabel::TaintLabel(const TaintLabelStore &parent, Val *origin, uint id) : originVal(origin), store(parent), tid(id) {
        if(id >= 64) {
            throw std::out_of_range("Can only have up to 64 taint labels per labelStore");
        }
    }

    std::size_t TaintLabel::hash() const {
        return (size_t) this;
    }

    const Val *TaintLabel::origin() {
        return originVal;
    }

    TaintLabel::~TaintLabel() {
        delete originVal;
    }

    const TaintLabelStore &TaintLabel::parent() const {
        return store;
    }

    uint TaintLabel::id() const {
        return tid;
    }

    uint64_t TaintLabel::taintMask() const {
        return 0x1 << tid;
    }
    bool TaintLabel::isGenerated() const {
        return parent().parent().isGenerated(this);
    }

    const llvm::Function *TaintLabel::generatedBy() const {
        if(parent().parent().isGenerated(this)) {
            return &parent().parent().function();
        }

        return nullptr;
    }
}