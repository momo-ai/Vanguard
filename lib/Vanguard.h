//
// Created by Jon Stephens on 3/19/22.
//

#ifndef VANGUARD_VANGUARD_H
#define VANGUARD_VANGUARD_H
#include <Blockchain.h>
#include <unordered_set>
#include "llvm/Pass.h"
#include "Requirement.h"
#include "Analysis.h"
#include "AARequirement.h"

namespace vanguard {
    class Vanguard {
    public:
        explicit Vanguard() : analysis(nullptr) {}
        ~Vanguard();
        const blockchain::Blockchain *blockchain(AARequirement *aa);
        void registerRequirement(Requirement *req);
    protected:
        Analysis *analysis;

        unordered_set<Requirement *> requirements;
        bool runToFixedpoint(Function &fn);
        vector<BasicBlock *> *reachableBlks(BasicBlock &blk, unordered_set<BasicBlock *> *exclude);
        void registerAnalysis(Analysis *a);
    private:
        const blockchain::Blockchain *chain = nullptr;
    };
}
#endif //VANGUARD_VANGUARD_H
