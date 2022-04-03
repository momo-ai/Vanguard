//
// Created by Jon Stephens on 3/29/22.
//

#include "TaintLabelStore.h"
#include "TaintLabel.h"

namespace vanguard {
    TaintLabelStore::TaintLabelStore(const TaintSummary &parent) : summary(parent), nextLabel(0) {}

    TaintLabelStore::~TaintLabelStore() {
        for(auto entry : idToLabel) {
            delete entry.second;
        }

        idToLabel.clear();
        maskToLabel.clear();
    }

    const TaintSummary &TaintLabelStore::parent() const {
        return summary;
    }

    TaintLabel *TaintLabelStore::newLabel(Val *origin) {
        auto l = new TaintLabel(*this, origin, nextLabel++);
        maskToLabel[l->taintMask()] = l;
        idToLabel[l->id()] = l;
        return l;
    }

    TaintLabel *TaintLabelStore::getLabelFromMask(uint64_t mask) const {
        return maskToLabel.at(mask);
    }

    TaintLabel *TaintLabelStore::getLabelFromId(uint id) const {
        return idToLabel.at(id);
    }
}