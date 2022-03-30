//
// Created by Jon Stephens on 3/29/22.
//

#ifndef VANGUARD_TAINTLABEL_H
#define VANGUARD_TAINTLABEL_H

#include <locale>
#include "TaintLabelStore.h"
#include "TaintNode.h"
#include "llvm/IR/Function.h"

namespace vanguard {
    class TaintLabel : public TaintNode {
    public:
        ~TaintLabel() = default;
        uint id() const;
        uint64_t taintMask() const;
    private:
        uint tid;
        explicit TaintLabel(uint id);

        friend class TaintLabelStore;
    };
}



#endif //VANGUARD_TAINTLABEL_H
