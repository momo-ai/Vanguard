//
// Created by Jon Stephens on 8/20/22.
//

#include "DetectorRegistry.h"
#include "FunctionPrinter/FunctionPrinter.h"

namespace vanguard {

    DetectorRegistry::DetectorRegistry() {
        add(FunctionPrinter<LLVMDomain>::name(),
            FunctionPrinter<LLVMDomain>::domain());
        add(StatGen<LLVMDomain>::name(), StatGen<LLVMDomain>::domain());
        add(IRValidator<LLVMDomain>::name(), IRValidator<LLVMDomain>::domain());
        add(ReentrancyDetector<BlockchainDomain>::name(),
            ReentrancyDetector<BlockchainDomain>::domain());
        add(PublicCallbacksDetector<BlockchainDomain>::name(),
            PublicCallbacksDetector<BlockchainDomain>::domain());
    }

    DetectorRegistry *DetectorRegistry::instance = nullptr;

    template <>
    UniverseDetector<LLVMDomain> *
    DetectorRegistry::get(const std::string &name) {
        return getGenericDetectors<LLVMDomain>(name);
    }

    template <>
    UniverseDetector<BlockchainDomain> *
    DetectorRegistry::get(const std::string &name) {
        if (name == PublicCallbacksDetector<BlockchainDomain>::name()) {
            return new PublicCallbacksDetector<BlockchainDomain>();
        } else if (name == ReentrancyDetector<BlockchainDomain>::name()) {
            return new ReentrancyDetector<BlockchainDomain>();
        }

        return getGenericDetectors<BlockchainDomain>(name);
    }

    DetectorRegistry &DetectorRegistry::getInstance() {
        if(instance == nullptr) {
            instance = new DetectorRegistry();
            //addToRegistry(instance);
        }

        return *instance;
    }

    Detector::DetectorDomain domainUnion(Detector::DetectorDomain d1, Detector::DetectorDomain d2) {
        return d1 > d2 ? d1 : d2;
    }

    Detector::DetectorDomain DetectorRegistry::domain(const std::vector<std::string>& detectorNames) {
        Detector::DetectorDomain domain = Detector::DetectorDomain::BASIC;

        for(const auto& name : detectorNames) {
            domain = domainUnion(domain, registry[name]);
        }

        return domain;
    }

    bool DetectorRegistry::add(const std::string& name, Detector::DetectorDomain domain) {
        if(registry.find(name) == registry.end()) {
            registry[name] = domain;
            return true;
        }

        return false;
    }

    std::vector<std::string> DetectorRegistry::all() {
        std::vector<std::string> detectors;

        for(auto &entry : registry) {
            detectors.push_back(entry.first);
        }

        return detectors;
    }
} // namespace vanguard
