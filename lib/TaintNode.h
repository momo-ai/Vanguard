//
// Created by Jon Stephens on 3/29/22.
//

#ifndef VANGUARD_TAINTNODE_H
#define VANGUARD_TAINTNODE_H

#include <vector>
#include <unordered_set>
#include "TaintSource.h"
#include "Val.h"

namespace vanguard {
    class TaintNode {
    public:
        void addNode(TaintNode *n);
        void addSource(TaintSource *s);
        std::unordered_set<TaintSource *> sources();
        void sources(std::unordered_set<TaintNode *> &seen, std::unordered_set<TaintSource *> &srcs);
        virtual const Val *origin() = 0;
        virtual std::size_t hash() const = 0;
    private:
        std::unordered_set<TaintNode *> children;
        std::vector<TaintSource *> leaves;
    };
}

namespace std {
    template <>
    struct hash<vanguard::TaintNode>
    {
        std::size_t operator()(const vanguard::TaintNode &node) const
        {
            return node.hash();
        }

        std::size_t operator()(const vanguard::TaintNode *node) const
        {
            return node->hash();
        }
    };
}

#endif //VANGUARD_TAINTNODE_H
