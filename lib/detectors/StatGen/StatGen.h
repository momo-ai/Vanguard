//
// Created by Jon Stephens on 8/14/22.
//

#ifndef VANGUARD_STATGEN_H
#define VANGUARD_STATGEN_H

#include "../UnitDetector.h"

namespace vanguard {
    class StatGen : public UnitDetector<Universe> {
    public:
        std::vector<Requirement *> registerAnalyses() override;
        void startDetection() override;
        void detect(Universe::CompilationUnit &unit) override;
        void report() override;

        static std::string name();

        static Detector::Domain domain() {
            return Detector::BASIC;
        }
    private:
        void countBody(Universe::Block *blk);

        int totFns = 0;
        int totIns = 0;
        int totBlks = 0;
    };
}



#endif //VANGUARD_STATGEN_H
