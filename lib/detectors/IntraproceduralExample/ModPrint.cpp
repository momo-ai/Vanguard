//
// Created by Jon Stephens on 3/20/22.
//

#include "ModPrint.h"
#include <iostream>

using namespace std;

namespace IntraExample {
    bool ModPrint::shouldAnalyze(Function &fn) {
        return true;
    }

    bool ModPrint::beginFn(Function &fn) {
        if(fn.hasName()) {
            cout << fn.getName().str() << endl;
        }

        return false;
    }

    bool ModPrint::transfer(Instruction &ins) {
        return false;
    }

    bool ModPrint::endFn(Function &fn) {
        return false;
    }

    string ModPrint::vulnerabilityReport()  {
        return "Done";
    }
}