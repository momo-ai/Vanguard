//
// Created by Kostas Ferles on 8/30/22.
//

#ifndef VANGUARD_NEAR_H
#define VANGUARD_NEAR_H

#include <map>

#include "Blockchain.h"
#include "../../../detectors/DAWrapper.h"

namespace blockchain {

    class Near : public Blockchain {
    public:

        Near(BlockchainToLLVM *blk2llvm, string &c, string &v, vector<BlkContract *> *contracts, vanguard::AAWrapper &alias);

        static inline bool classof(const Near &) { return true; }

        static inline bool classof(const Near *) { return true; }

        static inline bool classof(const BlkNode *node) { return classof(*node); }

        static inline bool classof(const BlkNode &node) {
            if(node.type() == NEAR) { return true; }
            return false;
        }

        bool allowsReentrancy() const override;

        bool readsStorage(vanguard::Instruction &ins) override;

        bool writesStorage(vanguard::Instruction &ins) override;

        bool getsSender(vanguard::Instruction &ins) const override;

        bool getsValue(vanguard::Instruction &ins) const override;

        bool isSelfDestruct(vanguard::Instruction &ins) const override;

        static std::string demangleRustName(const vanguard::Function& fun);

    // Private Methods
    private:

        size_t findVarOffset(BlkVariable &var, BlkContract &contract, vanguard::CompilationUnit &cu);

    // Private State
    private:

        vanguard::AAWrapper &alias;

        std::map<BlkContract*, std::map<std::string, size_t>> varOffsets;
    };

}



#endif //VANGUARD_NEAR_H
