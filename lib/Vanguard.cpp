//
// Created by Jon Stephens on 8/12/22.
//

#include "Vanguard.h"
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/IR/PassInstrumentation.h>
#include "detectors/StatGen/StatGen.h"
#include "detectors/FunctionPrinter/FunctionPrinter.h"
#include <llvm/Transforms/IPO/PassManagerBuilder.h>

//registering args: https://stackoverflow.com/questions/67206238/how-to-define-and-read-cli-arguments-for-an-llvm-pass-with-the-new-pass-manager
//#include "llvm/Support/CommandLine.h"
//cl::list<std::string> Lists("lists", cl::desc("Specify names"), cl::OneOrMore);

namespace vanguard {
    /*void vanguardPassEnded(llvm::StringRef passName, llvm::Any, const llvm::PreservedAnalyses &) {
        std::cout << passName.str() << std::endl;
    }*/

    bool registerVanguardFnPasses(llvm::StringRef name, llvm::FunctionPassManager &passMgr, llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
        if (name == "fnPrinter") {
            passMgr.addPass(vanguard::FunctionPrinter());
            return true;
        }
        return false;
    }

    bool registerVanguardModulePasses(llvm::StringRef name, llvm::ModulePassManager &passMgr, llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
        if (name == "statGen") {
            passMgr.addPass(vanguard::StatGen());
            return true;
        }
        return false;
    }

    void registerVanguardCallbacks(llvm::PassBuilder &PB) {
        PB.registerPipelineParsingCallback(registerVanguardModulePasses);
        PB.registerPipelineParsingCallback(registerVanguardFnPasses);
        //PB.getPassInstrumentationCallbacks()->registerAfterPassCallback(vanguardPassEnded);
    }
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize HelloWorld when added to the pass pipeline on the
// command line, i.e. via '-passes=hello-world'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "Vanguard", LLVM_VERSION_STRING, vanguard::registerVanguardCallbacks};
}