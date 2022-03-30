//
// Created by Jon Stephens on 3/30/22.
//

#ifndef VANGUARD_TAINTSINKPROVIDER_H
#define VANGUARD_TAINTSINKPROVIDER_H

#include <vector>
#include "TaintNode.h"
#include "FunctionTaintSink.h"

namespace vanguard {
    class TaintSinkProvider {
    public:
        virtual std::vector<TaintNode *> getTaint(FunctionTaintSink &sink) = 0;
    };
}



#endif //VANGUARD_TAINTSINKPROVIDER_H
