//
// Created by Jon Stephens on 9/18/22.
//

#ifndef VANGUARD_LIBBLOCKCHAIN_UNIVERSE_H
#define VANGUARD_LIBBLOCKCHAIN_UNIVERSE_H

#include "Blockchain.h"
#include <string>

namespace vanguard {
    template<class Base, class Domain>
    class Blockchain<Base, Domain>::Universe : public Base::Universe {
    public:
        template<typename ...Args>
        explicit Universe(Args&&... args) : Base::Universe(std::forward<Args>(args)...) {};

        std::vector<typename Domain::Contract *> contracts() const {
            std::vector<typename Domain::Contract *> contracts;
            for(auto unit : this->units()) {
                for(auto contract : unit->contracts()) {
                    contracts.push_back(contract);
                }
            }

            return contracts;
        }
    };
}


#endif //VANGUARD_UNIVERSE_H
