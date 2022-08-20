//
// Created by Jon Stephens on 8/20/22.
//

#ifndef VANGUARD_PROGRAMDETECTOR_H
#define VANGUARD_PROGRAMDETECTOR_H

#include "Detector.h"
#include "../program/Program.h"

namespace vanguard {
    class ProgramDetector : public Detector {
    public:
        virtual ~ProgramDetector() = default;
        virtual void detect(Program &prog) = 0;
    };
}



#endif //VANGUARD_PROGRAMDETECTOR_H
