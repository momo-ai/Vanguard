//
// Created by Jon Stephens on 8/13/22.
//

#ifndef VANGUARD_DETECTOR_H
#define VANGUARD_DETECTOR_H
namespace vanguard {
    class Detector {
    public:
        virtual void registerAnalyses() = 0;
        virtual void startDetection() = 0;
        virtual void report() = 0;
    };
}
#endif //VANGUARD_DETECTOR_H
