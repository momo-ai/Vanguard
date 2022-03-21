//
// Created by Jon Stephens on 3/20/22.
//

#include "ModPrint.h"
#include <iostream>

using namespace std;

namespace IntraExample {
    bool ModPrint::shouldAnalyze(const Function &fn) {
        return true;
    }

    bool ModPrint::beginFn(const Function &fn) {
        if(fn.hasName()) {
            cout << fn.getName().str() << endl;
        }

        return false;
    }

    bool ModPrint::transfer(const Instruction &ins) {
        return false;
    }

    bool ModPrint::endFn(const Function &fn) {
        return false;
    }

    string ModPrint::vulnerabilityReport()  {
        return "Done";
    }
}