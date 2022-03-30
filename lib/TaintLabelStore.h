//
// Created by Jon Stephens on 3/29/22.
//

#ifndef VANGUARD_TAINTLABELSTORE_H
#define VANGUARD_TAINTLABELSTORE_H

#include <unordered_map>
#include <locale>


namespace vanguard {
    class TaintLabel;

    class TaintLabelStore {
    public:
        TaintLabelStore() = default;
        TaintLabel *newLabel();
        TaintLabel *getLabelFromMask(uint64_t mask) const;
        TaintLabel *getLabelFromId(uint id) const;
    private:
        uint nextLabel;
        std::unordered_map<uint64_t, TaintLabel *> maskToLabel;
        std::unordered_map<uint, TaintLabel *> idToLabel;
    };
}



#endif //VANGUARD_TAINTLABELSTORE_H
