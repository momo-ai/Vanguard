//
// Created by Jon Stephens on 8/14/22.
//

#ifndef VANGUARD_IRVALIDATOR_H
#define VANGUARD_IRVALIDATOR_H

#include "../UnitDetector.h"

namespace vanguard {
    class IRValidator : public UnitDetector<IRValidator> {
    public:
        void registerAnalyses() override;
        void startDetection() override;
        void detect(CompilationUnit &unit) override;
        void report() override;
    private:
        void countBody(Block *blk);

        int totFns = 0;
        int totIns = 0;
        int totBlks = 0;
        std::string moduleName;
        std::string sourceFileName;
    };
}



#endif //VANGUARD_IRVALIDATOR_H
