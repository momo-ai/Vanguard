//
// Created by Jon Stephens on 8/13/22.
//

#ifndef VANGUARD_DETECTOR_H
#define VANGUARD_DETECTOR_H

#include "../analysis/Requirement.h"

namespace vanguard {
    class Detector {
    public:
        enum DetectorDomain { BASIC, BLOCKCHAIN };

        virtual std::vector<Requirement *> registerAnalyses() {
            return {};
        }

        virtual void startDetection() {};
        virtual void report() = 0;
    };
}
#endif //VANGUARD_DETECTOR_H
