//
// Created by Jon Stephens on 8/13/22.
//

#ifndef VANGUARD_DETECTOR_H
#define VANGUARD_DETECTOR_H

#include "../analysis/Requirement.h"

namespace vanguard {
    class Detector {
    public:
        virtual std::vector<Requirement *> registerAnalyses() = 0;
        virtual void startDetection() = 0;
        virtual void report() = 0;
    };
}
#endif //VANGUARD_DETECTOR_H
