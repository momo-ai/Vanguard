//
// Created by Jon Stephens on 3/29/22.
//

#ifndef VANGUARD_TAINTSINK_H
#define VANGUARD_TAINTSINK_H

#include <vector>
#include "TaintNode.h"

namespace vanguard {
    class TaintSinkProvider;

    class TaintSink {
    public:
        TaintSink() = default;
        virtual std::vector<TaintNode *> gatherTaint() = 0;
        void registerProvider(TaintSinkProvider *l);
        std::unordered_set<TaintSource *> sources();
    protected:
        std::vector<TaintSinkProvider *> providers;
    };
}


#endif //VANGUARD_TAINTSINK_H
