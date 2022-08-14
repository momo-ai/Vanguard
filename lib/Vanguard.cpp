//
// Created by Jon Stephens on 8/12/22.
//

#include "Vanguard.h"
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include "detectors/FunctionPrinter/FunctionPrinter.h"


namespace vanguard {
}

llvm::PassPluginLibraryInfo getVanguardPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "Vanguard", LLVM_VERSION_STRING,
            [](llvm::PassBuilder &PB) {
                PB.registerPipelineParsingCallback(
                        [](llvm::StringRef Name, llvm::FunctionPassManager &FPM,
                           llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
                            if (Name == "fnPrinter") {
                                FPM.addPass(vanguard::FunctionPrinter());
                                return true;
                            }
                            /*else if(Name == "test1") {
                                FPM.addPass(vanguard::Test1());
                                return true;
                            }*/
                            return false;
                        });
            }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize HelloWorld when added to the pass pipeline on the
// command line, i.e. via '-passes=hello-world'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return getVanguardPluginInfo();
}
