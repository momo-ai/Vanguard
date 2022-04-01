//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_VANGUARD_H
#define VANGUARD_VANGUARD_H
#include "Analysis.h"
#include <Blockchain.h>
#include <unordered_set>
#include "llvm/Pass.h"

namespace vanguard {
    class Vanguard {
    public:
        explicit Vanguard() : analysis(nullptr) {}
        const blockchain::Blockchain *blockchain();
    protected:
        Analysis *analysis;

        bool runToFixedpoint(Function &fn);
        vector<BasicBlock *> *reachableBlks(BasicBlock &blk, unordered_set<BasicBlock *> *exclude);
        virtual void registerAnalysis(Analysis *a);
    private:
        const blockchain::Blockchain *chain = nullptr;
    };
}
#endif //VANGUARD_VANGUARD_H
