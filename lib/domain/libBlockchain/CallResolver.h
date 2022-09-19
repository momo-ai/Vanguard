//
// Created by Jon Stephens on 9/6/22.
//

#ifndef VANGUARD_CALLRESOLVER_H
#define VANGUARD_CALLRESOLVER_H

#include <vector>
#include <program/InstructionClasses.h>

namespace vanguard {
    template<typename Domain>
    class CallResolver {
    public:
        virtual std::vector<typename Domain::Function *> resolve(const CallIns<Domain> &call, typename Domain::Universe &universe)  = 0;
    };
}


#endif //VANGUARD_CALLRESOLVER_H
