//
// Created by Jon Stephens on 8/20/22.
//

#ifndef VANGUARD_UNIVERSEDETECTOR_H
#define VANGUARD_UNIVERSEDETECTOR_H

#include "Detector.h"
#include "program/Universe.h"

namespace vanguard {

    template<class Domain>
    class UniverseDetector : public Detector {
    public:
        virtual ~UniverseDetector() = default;
        virtual void detect(Domain &universe) = 0;
    };
}



#endif //VANGUARD_UNIVERSEDETECTOR_H
