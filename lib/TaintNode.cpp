//
// Created by Jon Stephens on 3/29/22.
//

#include "TaintNode.h"
#include <algorithm>
#include <unordered_set>

using namespace llvm;
using namespace std;

namespace vanguard {
    void TaintNode::addNode(TaintNode *n) {
        if(n != nullptr) {
            children.insert(n);
        }
    }

    void TaintNode::addSource(TaintSource *s) {
        if(s != nullptr) {
            leaves.push_back(s);
        }
    }

    void TaintNode::generatingFns(unordered_set<const TaintNode *> &seen, unordered_set<const Function *> &generators) const {
        if(seen.find(this) != seen.end()) {
            return;
        }

        seen.insert(this);
        const Function *gen = generatedBy();
        if(gen != nullptr) {
            generators.insert(gen);
            return;
        }

        for(auto child : children) {
            child->generatingFns(seen, generators);
        }
    }

    std::unordered_set<TaintSource *> TaintNode::sources() {
        std::unordered_set<TaintNode *> seen;
        std::unordered_set<TaintSource *> srcs;
        sources(seen, srcs);
        return srcs;
    }

    void TaintNode::sources(unordered_set<TaintNode *> &seen, unordered_set<TaintSource *> &srcs) {
        if(seen.find(this) != seen.end()) {
            return;
        }

        seen.insert(this);
        srcs.insert(leaves.begin(), leaves.end());
        for(auto child : children) {
            child->sources(seen, srcs);
        }
    }
}