//
// Created by Jon Stephens on 3/29/22.
//

#ifndef VANGUARD_TAINTNODE_H
#define VANGUARD_TAINTNODE_H

#include <vector>
#include <unordered_set>
#include "TaintSource.h"

namespace vanguard {
    class TaintNode {
    public:
        void addNode(TaintNode *n);
        void addSource(TaintSource *s);
        std::unordered_set<TaintSource *> sources();
        void sources(std::unordered_set<TaintNode *> &seen, std::unordered_set<TaintSource *> &srcs);
    private:
        std::vector<TaintNode *> children;
        std::vector<TaintSource *> leaves;
    };
}

#endif //VANGUARD_TAINTNODE_H
