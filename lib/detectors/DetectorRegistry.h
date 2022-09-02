//
// Created by Jon Stephens on 8/20/22.
//

#ifndef VANGUARD_REGISTRY_H
#define VANGUARD_REGISTRY_H

#include <unordered_map>
#include "FunctionPrinter/FunctionPrinter.h"

namespace vanguard {
    class DetectorRegistry {
    public:
        static DetectorRegistry &getInstance();

        template<typename Domain>
        UniverseDetector<Domain> *get(const std::string& name) {
            if(name == FunctionPrinter<Domain>::name()) {
                return new FunctionPrinter<Domain>();
            }

            return nullptr;
        };

        bool add(const std::string& name, Detector::DetectorDomain domain);

        Detector::DetectorDomain domain(const std::vector<std::string>& detectorNames);

        std::vector<std::string> all();

    private:
        static DetectorRegistry *instance;
        std::unordered_map<std::string, Detector::DetectorDomain> registry;

        DetectorRegistry() {
            //assert(add(StatGen::name(), StatGen::domain()));
            add(FunctionPrinter<Universe>::name(), FunctionPrinter<Universe>::domain());
            //add(ReentrancyDetector::name(), new ReentrancyDetector(summary.getValue()));
            // add(IRValidator::name(), new IRValidator());
        }
    };
}



#endif //VANGUARD_REGISTRY_H
