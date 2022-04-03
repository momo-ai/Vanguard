//
// Created by Jon Stephens on 3/29/22.
//

#ifndef VANGUARD_TAINTLABELSTORE_H
#define VANGUARD_TAINTLABELSTORE_H

#include <unordered_map>
#include <locale>
#include "Val.h"


namespace vanguard {
    class TaintLabel;
    class TaintSummary;

    class TaintLabelStore {
    public:
        TaintLabelStore(const TaintSummary &parent);
        ~TaintLabelStore();
        TaintLabel *newLabel(Val *origin);
        TaintLabel *getLabelFromMask(uint64_t mask) const;
        TaintLabel *getLabelFromId(uint id) const;
        const TaintSummary &parent() const;
    private:
        uint nextLabel;
        std::unordered_map<uint64_t, TaintLabel *> maskToLabel;
        std::unordered_map<uint, TaintLabel *> idToLabel;
        const TaintSummary &summary;
    };
}



#endif //VANGUARD_TAINTLABELSTORE_H
