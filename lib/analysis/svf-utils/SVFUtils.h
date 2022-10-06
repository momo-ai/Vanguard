//
// Created by Kostas Ferles on 10/6/22.
//

#ifndef VANGUARD_SVFUTILS_H
#define VANGUARD_SVFUTILS_H

#include <SVF-FE/LLVMUtil.h>
#include <Util/Options.h>
#include <Graphs/SVFG.h>
#include <WPA/Andersen.h>
#include <SVF-FE/SVFIRBuilder.h>

namespace analysis {

    class SVFUtils {

        static SVF::SVFModule* getSVFModule() {
            if (svfModule == nullptr) {
                svfModule = SVF::LLVMModuleSet::getLLVMModuleSet()->getSVFModule();
            }

            return svfModule;
        }

        static SVF::SVFIR* getPAG() {
            if (pag == nullptr) {
                auto mod = getSVFModule();
                SVF::SVFIRBuilder builder;
                pag = builder.build(mod);
            }

            return pag;
        }

        static SVF::PointerAnalysis* getPointerAnalysis() {
            if (pa == nullptr) {
                auto _pag = getPAG();
                // TODO: make the following configurable
                pa = SVF::AndersenWaveDiff::createAndersenWaveDiff(_pag);
            }

            return pa;
        }

        static SVF::PTACallGraph* getCallGraph() {
            if (callgraph == nullptr) {
                auto _pa = getPointerAnalysis();
                callgraph = _pa->getPTACallGraph();
            }

            return callgraph;
        }

        static SVF::VFG* getVFG() {
            if (vfg == nullptr) {
                auto cg = getCallGraph();
                vfg = new SVF::VFG(cg);
            }

            return vfg;
        }

    private:
        static SVF::SVFModule *svfModule;

        static SVF::SVFIR *pag;

        static SVF::PointerAnalysis *pa;

        static SVF::PTACallGraph *callgraph;

        static SVF::VFG *vfg;

    };

}


#endif //VANGUARD_SVFUTILS_H
