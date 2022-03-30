//
// Created by Jon Stephens on 3/29/22.
//

#ifndef VANGUARD_TAINTSINK_H
#define VANGUARD_TAINTSINK_H

#include <vector>
#include "TaintNode.h"

namespace vanguard {
    class TaintSink {
    public:
        void addTaint(TaintNode * node);
        std::unordered_set<TaintSource *> sources();
    protected:
        std::vector<TaintNode *> taintedBy;
    };
}


#endif //VANGUARD_TAINTSINK_H
