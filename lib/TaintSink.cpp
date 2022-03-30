//
// Created by Jon Stephens on 3/29/22.
//

#include "TaintSink.h"

namespace vanguard {
    void TaintSink::addTaint(TaintNode *node) {
        if(node == nullptr) {
            return;
        }

        taintedBy.push_back(node);
    }

    std::unordered_set<TaintSource *> TaintSink::sources() {
        std::unordered_set<TaintNode *> seen;
        std::unordered_set<TaintSource *> srcs;

        for(auto child : taintedBy) {
            child->sources(seen, srcs);
        }

        return srcs;
    }
}