//
// Created by Jon Stephens on 8/20/22.
//

#include "DetectorRegistry.h"
#include "StatGen/StatGen.h"
#include "FunctionPrinter/FunctionPrinter.h"
#include "Reentrancy/ReentrancyDetector.h"
#include <llvm/Support/CommandLine.h>

/* This is how you can add additional detectors from external sources. Essentially add them in at compile time and
 * then in a cpp file, implement the addToRegistry function.
extern "C"
void addToRegistry(vanguard::DetectorRegistry *registry) {
    registry->add(Detector::name(), new Detector());
}
 */

static llvm::cl::opt<std::string> summary("summary", llvm::cl::desc("Blockchain Summary"), llvm::cl::value_desc("filename"), llvm::cl::Optional);


extern "C" __attribute__((__weak__))
void addToRegistry(vanguard::DetectorRegistry *registry) {}

namespace vanguard {
    DetectorRegistry *DetectorRegistry::instance = nullptr;
    DetectorRegistry &DetectorRegistry::getInstance() {
        if(instance == nullptr) {
            instance = new DetectorRegistry();
            addToRegistry(instance);
        }

        return *instance;
    }

    DetectorRegistry::DetectorRegistry() {
        add(StatGen::name(), new StatGen());
        add(FunctionPrinter::name(), new FunctionPrinter());
        add(ReentrancyDetector::name(), new ReentrancyDetector(summary.getValue()));
    }

    DetectorRegistry::~DetectorRegistry() {
        for(auto &entry : registry) {
            delete entry.second;
        }
        registry.clear();
    }

    bool DetectorRegistry::add(const std::string& name, ProgramDetector *detect) {
        if(registry.find(name) == registry.end()) {
            registry[name] = detect;
            return true;
        }

        return false;
    }

    ProgramDetector *DetectorRegistry::get(const std::string& name) {
        if(registry.find(name) == registry.end()) {
            return nullptr;
        }

        return registry[name];
    }

    std::vector<ProgramDetector *> DetectorRegistry::all() {
        std::vector<ProgramDetector *> detectors;

        for(auto &entry : registry) {
            detectors.push_back(entry.second);
        }

        return detectors;
    }
}