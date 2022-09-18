//
// Created by Jon Stephens on 8/20/22.
//

#ifndef VANGUARD_REGISTRY_H
#define VANGUARD_REGISTRY_H

#include "program/Base.h"
#include <unordered_map>
#include "FunctionPrinter/FunctionPrinter.h"
//#include "Reentrancy/ReentrancyDetector.h"
#include "StatGen/StatGen.h"
#include "IRValidator/IRValidator.h"
#include "program/Factory.h"

namespace vanguard {
    class LLVMDomain : public Base<LLVMDomain> {
    /*public:
        template<typename ...Args>
        explicit LLVMDomain(Args&&... args) : Base<LLVMDomain>(std::forward<Args>(args)...) {};*/
    };

    class DetectorRegistry {
    public:
        static DetectorRegistry &getInstance();

        template<typename Domain>
        UniverseDetector<Domain> *get(const std::string& name) {
            /*if(name == FunctionPrinter<Domain>::name()) {
                return new FunctionPrinter<Domain>();
            }
            else if(name == StatGen<Domain>::name()) {
                return new StatGen<Domain>();
            }
            else if(name == IRValidator<Domain>::name()) {
                return new IRValidator<Domain>();
            }
            else if(name == ReentrancyDetector<Domain>::name()) {
                return new ReentrancyDetector<Domain>();
            }*/

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
            add(FunctionPrinter<LLVMDomain>::name(), FunctionPrinter<LLVMDomain>::domain());
            add(StatGen<LLVMDomain>::name(), StatGen<LLVMDomain>::domain());
            add(IRValidator<LLVMDomain>::name(), IRValidator<LLVMDomain>::domain());
            //add(ReentrancyDetector<Universe>::name(), ReentrancyDetector<Universe>::domain());
            //add(ReentrancyDetector::name(), new ReentrancyDetector(summary.getValue()));
            // add(IRValidator::name(), new IRValidator());
        }
    };
}



#endif //VANGUARD_REGISTRY_H
