//
// Created by Jon Stephens on 3/29/22.
//

#include "TaintLabelStore.h"
#include "TaintLabel.h"

namespace vanguard {
    TaintLabelStore::~TaintLabelStore() {
        for(auto entry : idToLabel) {
            delete entry.second;
        }

        idToLabel.clear();
        maskToLabel.clear();
    }

    TaintLabel *TaintLabelStore::newLabel() {
        auto l = new TaintLabel(nextLabel++);
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