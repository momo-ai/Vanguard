//
// Created by Jon Stephens on 3/29/22.
//

#include "FunctionTaintSink.h"
#include "TaintSinkProvider.h"

namespace vanguard {
    std::vector<TaintNode *> FunctionTaintSink::gatherTaint() {
        std::vector<TaintNode *> taint;
        for(auto provider : providers) {
            auto providedTaint = provider->getTaint(*this);
            taint.insert(taint.end(), providedTaint.begin(), providedTaint.end());
        }

        return taint;
    }
}