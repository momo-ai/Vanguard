//
// Created by Jon Stephens on 8/12/22.
//

#ifndef VANGUARD_VANGUARD_H
#define VANGUARD_VANGUARD_H

#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>

namespace vanguard {
    class Vanguard {
    public:
        //Utility Functions
        static llvm::raw_ostream &out() { return llvm::outs(); };
        static llvm::raw_ostream &err() { return llvm::errs(); };
    };
}



#endif //VANGUARD_VANGUARD_H
