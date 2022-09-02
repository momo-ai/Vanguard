//
// Created by Jon Stephens on 8/14/22.
//

#ifndef VANGUARD_IRVALIDATOR_H
#define VANGUARD_IRVALIDATOR_H

#include "../UnitDetector.h"

namespace vanguard {
    template<typename Domain>
    class IRValidator : public UnitDetector<Domain> {
    public:
        std::vector<Requirement *> registerAnalyses() override;
        void startDetection() override;
        void detect(typename Domain::CompilationUnit &unit) override;
        void report() override;

        static std::string name();

        static Detector::Domain domain() {
            return Detector::BASIC;
        }
    private:
        void countBody(typename Domain::Block *blk);

        int totFns = 0;
        int totIns = 0;
        int totBlks = 0;
        std::string moduleName;
        std::string sourceFileName;
    };
}



#endif //VANGUARD_IRVALIDATOR_H
