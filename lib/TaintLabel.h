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
        ~TaintLabel();
        uint id() const;
        uint64_t taintMask() const;
        const TaintLabelStore &parent() const;
        const Val *origin() override;
        std::size_t hash() const override;
        bool isGenerated() const override;
        const llvm::Function *generatedBy() const override;
    private:
        uint tid;
        Val *originVal;
        const TaintLabelStore &store;
        explicit TaintLabel(const TaintLabelStore &parent, Val *origin, uint id);

        friend class TaintLabelStore;
    };
}



#endif //VANGUARD_TAINTLABEL_H
