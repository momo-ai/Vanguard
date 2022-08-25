//
// Created by Jon Stephens on 8/14/22.
//

#ifndef VANGUARD_STATGEN_H
#define VANGUARD_STATGEN_H

#include "../UnitDetector.h"

namespace vanguard {
    class StatGen : public UnitDetector {
    public:
        std::vector<Requirement *> registerAnalyses() override;
        void startDetection() override;
        void detect(CompilationUnit &unit) override;
        void report() override;

        static std::string name();
    private:
        void countBody(Block *blk);

        int totFns = 0;
        int totIns = 0;
        int totBlks = 0;
    };
}



#endif //VANGUARD_STATGEN_H
