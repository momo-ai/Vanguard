#ifndef VANGUARD_DOMAIN_CALLEDGE_H
#define VANGUARD_DOMAIN_CALLEDGE_H

#include "../program/Function.h"

namespace vanguard {
    class CallEdge {
        Function* caller();
        Function* callee();
    };
}

#endif
