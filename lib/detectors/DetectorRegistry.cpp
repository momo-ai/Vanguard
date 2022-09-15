//
// Created by Jon Stephens on 8/20/22.
//

#include "DetectorRegistry.h"
//#include "StatGen/StatGen.h"
//#include "IRValidator/IRValidator.h"
#include "FunctionPrinter/FunctionPrinter.h"
#include "domain/libBlockchain/Blockchain.h"
//#include "Reentrancy/ReentrancyDetector.h"
#include <llvm/Support/CommandLine.h>
#include <program/Top.h>

/* This is how you can add additional detectors from external sources. Essentially add them in at compile time and
 * then in a cpp file, implement the addToRegistry function.
extern "C"
void addToRegistry(vanguard::DetectorRegistry *registry) {
    registry->add(Detector::name(), new Detector());
}
 */

static llvm::cl::opt<std::string> summary("summary", llvm::cl::desc("Blockchain Summary"), llvm::cl::value_desc("filename"), llvm::cl::Optional);


//extern "C" __attribute__((__weak__))
//void addToRegistry(vanguard::DetectorRegistry *registry) {}

namespace vanguard {
    DetectorRegistry *DetectorRegistry::instance = nullptr;

    template<>
    UniverseDetector<Top<Universe>> *DetectorRegistry::get(const std::string& name) {
        if(name == FunctionPrinter<Universe>::name()) {
            return new FunctionPrinter<Top<Universe>>();
        }
        else if(name == StatGen<Universe>::name()) {
            return new StatGen<Top<Universe>>();
        }
        else if(name == IRValidator<Universe>::name()) {
            return new IRValidator<Top<Universe>>();
        }
        /*else if(name == ReentrancyDetector<Domain>::name()) {
            return new ReentrancyDetector<Domain>();
        }*/

        return nullptr;
    };

    template<>
    UniverseDetector<Top<Blockchain<Universe>>> *DetectorRegistry::DetectorRegistry::get(const std::string& name) {
        if(name == FunctionPrinter<Blockchain<Universe>>::name()) {
            return new FunctionPrinter<Top<Blockchain<Universe>>>();
        }
        else if(name == StatGen<Blockchain<Universe>>::name()) {
            return new StatGen<Top<Blockchain<Universe>>>();
        }
        else if(name == IRValidator<Blockchain<Universe>>::name()) {
            return new IRValidator<Top<Blockchain<Universe>>>();
        }
        else if(name == ReentrancyDetector<Blockchain<Universe>>::name()) {
            return new ReentrancyDetector<Top<Blockchain<Universe>>>();
        }

        return nullptr;
    };

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
}