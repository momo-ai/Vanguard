//
// Created by Jon Stephens on 8/20/22.
//

#ifndef VANGUARD_REGISTRY_H
#define VANGUARD_REGISTRY_H

#include <unordered_map>
#include "ProgramDetector.h"

namespace vanguard {
    class DetectorRegistry {
    public:
        ~DetectorRegistry();
        static DetectorRegistry &getInstance();
        bool add(const std::string& name, ProgramDetector *detect);
        ProgramDetector *get(const std::string& name);
        std::vector<ProgramDetector *> all();

    private:
        static DetectorRegistry *instance;
        std::unordered_map<std::string, ProgramDetector *> registry;
        DetectorRegistry();
    };
}



#endif //VANGUARD_REGISTRY_H
