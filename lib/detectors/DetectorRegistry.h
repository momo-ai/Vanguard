//
// Created by Jon Stephens on 8/20/22.
//

#ifndef VANGUARD_REGISTRY_H
#define VANGUARD_REGISTRY_H

#include "FunctionPrinter/FunctionPrinter.h"
#include "IRValidator/IRValidator.h"
#include "NEAR/PublicCallbacks/PublicCallbacksDetector.h"
#include "Reentrancy/ReentrancyDetector.h"
#include "StatGen/StatGen.h"
#include "detectors/UniverseDetector.h"
#include "program/Base.h"
#include "program/Factory.h"
#include <domain/libBlockchain/Blockchain.h>
#include <domain/libBlockchain/Factory.h>
#include <domain/libBlockchain/Universe.h>
#include <unordered_map>

namespace vanguard {
    class BlockchainDomain : public Blockchain<Base<BlockchainDomain>, BlockchainDomain> {
    };

    class LLVMDomain : public Base<LLVMDomain> {
    };

    class DetectorRegistry {
    public:
        static DetectorRegistry &getInstance();

        template<typename Domain>
        UniverseDetector<Domain> *get(const std::string& name) {
            return getGenericDetectors<Domain>(name);
        }

        /**
         * Get detectors that work for all domains.
         */
        template <typename Domain>
        UniverseDetector<Domain> *getGenericDetectors(const std::string &name) {
            if (name == FunctionPrinter<Domain>::name()) {
                return new FunctionPrinter<Domain>();
            } else if (name == StatGen<Domain>::name()) {
                return new StatGen<Domain>();
            } else if (name == IRValidator<Domain>::name()) {
                return new IRValidator<Domain>();
            }

            return nullptr;
        }

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
            add(ReentrancyDetector<BlockchainDomain>::name(), ReentrancyDetector<BlockchainDomain>::domain());
            add(PublicCallbacksDetector<BlockchainDomain>::name(), PublicCallbacksDetector<BlockchainDomain>::domain());
            //add(ReentrancyDetector::name(), new ReentrancyDetector(summary.getValue()));
            // add(IRValidator::name(), new IRValidator());
        }
    };

    template <> UniverseDetector<LLVMDomain> *DetectorRegistry::get(const std::string &name);
    template <>
    UniverseDetector<BlockchainDomain> *DetectorRegistry::get(const std::string &name);
} // namespace vanguard



#endif //VANGUARD_REGISTRY_H
