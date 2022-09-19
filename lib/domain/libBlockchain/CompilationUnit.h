//
// Created by Jon Stephens on 9/18/22.
//

#ifndef VANGUARD_LIBBLOCKCHAIN_COMPILATIONUNIT_H
#define VANGUARD_LIBBLOCKCHAIN_COMPILATIONUNIT_H

#include "Blockchain.h"

namespace vanguard {
    template<typename Base, typename Domain>
    class Blockchain<Base, Domain>::CompilationUnit : public Base::CompilationUnit {
    public:
        template<typename ...Args>
        explicit CompilationUnit(std::vector<typename Domain::Contract *> contracts, Args&&... args) : unitContracts(contracts), Base::CompilationUnit(std::forward<Args>(args)...) {};

        template<typename ...Args>
        explicit CompilationUnit(Args&&... args) : Base::CompilationUnit(std::forward<Args>(args)...) {};

        std::vector<typename Domain::Contract *> contracts() const {
            return unitContracts;
        }
    private:
        std::vector<typename Domain::Contract *> unitContracts;
    };
}

#endif //VANGUARD_COMPILATIONUNIT_H
