//
// Created by Jon Stephens on 9/5/22.
//

#ifndef VANGUARD_REACHABLE_H
#define VANGUARD_REACHABLE_H

#include <unordered_set>
#include <queue>

namespace vanguard {

    template<typename Domain>
    class Reachable {
    public:
        virtual bool condition(typename Domain::Instruction &ins) = 0;

        bool reachable(typename Domain::Instruction &ins) {
            auto blk = ins.block();

            bool found = false;
            for (auto *curIns: blk->instructions()) {
                if (curIns == &ins) {
                    found = true;
                }

                if (found && condition(*curIns)) {
                    return true;
                }
            }

            std::queue<typename Domain::Block *> worklist;
            std::unordered_set<typename Domain::Block *> seen;

            for(auto succ : blk->successors()) {
                worklist.push(succ);
                seen.insert(succ);
            }

            while (!worklist.empty()) {
                auto curBlk = worklist.front();
                worklist.pop();

                for (auto curIns: curBlk->instructions()) {
                    if (found && condition(*curIns)) {
                        return true;
                    }
                }

                for (auto succ: curBlk->successors()) {
                    if (seen.find(succ) == seen.end()) {
                        worklist.push(succ);
                        seen.insert(succ);
                    }
                }
            }

            return false;
        }
    };
}

#endif //VANGUARD_REACHABLE_H
