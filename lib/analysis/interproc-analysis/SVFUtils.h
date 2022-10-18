//
// Created by Kostas Ferles on 10/6/22.
//

#ifndef VANGUARD_SVFUTILS_H
#define VANGUARD_SVFUTILS_H

#include <map>
#include <set>

#include <SVF-FE/LLVMUtil.h>
#include <Util/Options.h>
#include <Graphs/SVFG.h>
#include <WPA/Andersen.h>
#include <SVF-FE/SVFIRBuilder.h>
#include <Graphs/SVFGNode.h>

namespace analysis {

    class SVFUtils {
    public:

        static bool dependsOnTrg(const llvm::Value *src, const llvm::Value *trg);

        static std::vector<const llvm::Value*> valueMemDeps(const llvm::Value *src);

    private:
        static SVF::SVFModule *svfModule;

        static SVF::SVFIR *pag;

        static SVF::BVDataPTAImpl *pa;

        static SVF::PTACallGraph *callgraph;

        static SVF::SVFG *svfg;

        static std::map<const llvm::Value*, std::set<const SVF::VFGNode*>> cachedDeps;

        static void initSVFModule();

        static void initPAG();

        static void initPointerAnalysis();

        static void initCallGraph();

        static void initSVFG();

        static bool traverseMemDependencies(const llvm::Value *src, std::set<const SVF::VFGNode*> &deps, const llvm::Value *trg = nullptr);
    };

}


#endif //VANGUARD_SVFUTILS_H
