//
// Created by Jon Stephens on 9/2/22.
//

#ifndef VANGUARD_HELPERFUNCTION_H
#define VANGUARD_HELPERFUNCTION_H

#include "Blockchain.h"

namespace vanguard {
    template<class Domain>
    class HelperFunction : public Blockchain<Domain>::Function {
    public:
        template<typename ...Args>
        explicit HelperFunction(Args&&... args) : Blockchain<Domain>::Function(std::forward<Args>(args)...) {};

        bool isHelper() const override {
            return true;
        }
    };
}

#endif //VANGUARD_HELPERFUNCTION_H
