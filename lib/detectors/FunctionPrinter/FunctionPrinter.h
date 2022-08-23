//
// Created by Jon Stephens on 8/13/22.
//

#ifndef VANGUARD_FUNCTIONPRINTER_H
#define VANGUARD_FUNCTIONPRINTER_H

#include "../FunctionDetector.h"

namespace vanguard {
    class FunctionPrinter : public FunctionDetector {
    public:
        void registerAnalyses() override;
        void startDetection() override;
        bool detect(Function &fn) override;
        void report() override;

        static std::string name();
    private:
    };
}



#endif //VANGUARD_FUNCTIONPRINTER_H
