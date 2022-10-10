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

        static bool dependsOnTrg(const llvm::Value *src, const llvm::Value *trg) {
            if (cachedDeps.find(src) == cachedDeps.end()) {
                std::set<const SVF::VFGNode*> deps;
                return traverseMemDependencies(src, deps, trg);
            }
            else {
                auto deps = cachedDeps[src];
                return std::any_of(deps.begin(), deps.end(), [&trg](auto node) { return node->getValue() == trg; });
            }
        }

        static std::vector<const llvm::Value*> valueMemDeps(const llvm::Value *src) {
            if (cachedDeps.find(src) == cachedDeps.end()) {
                std::set<const SVF::VFGNode*> deps;
                traverseMemDependencies(src, deps);
                cachedDeps[src] = deps;
            }

            // Convert VFGNode -> llvm::Value
            std::vector<const llvm::Value*> valDeps;
            std::set<const SVF::VFGNode*> &memDeps = cachedDeps[src];
            std::transform(memDeps.begin(), memDeps.end(), std::back_inserter(valDeps),
                           [](auto mDep) { return mDep->getValue();});

            // Filter out null values
            std::vector<const llvm::Value*> nonNullValDeps;
            std::copy_if(valDeps.begin(), valDeps.end(), std::back_inserter(nonNullValDeps),
                         [](auto val) { return val != nullptr;});
            return std::move(nonNullValDeps);
        }

    private:
        static SVF::SVFModule *svfModule;

        static SVF::SVFIR *pag;

        static SVF::BVDataPTAImpl *pa;

        static SVF::PTACallGraph *callgraph;

        static SVF::SVFG *svfg;

        static std::map<const llvm::Value*, std::set<const SVF::VFGNode*>> cachedDeps;

        static void initSVFModule() {
            if (svfModule == nullptr) {
                svfModule = SVF::LLVMModuleSet::getLLVMModuleSet()->getSVFModule();
            }
        }

        static void initPAG() {
            if (pag == nullptr) {
                initSVFModule();
                SVF::SVFIRBuilder builder;
                pag = builder.build(svfModule);
            }
        }

        static void initPointerAnalysis() {
            if (pa == nullptr) {
                initPAG();
                // TODO: make the following configurable
                pa = SVF::AndersenWaveDiff::createAndersenWaveDiff(pag);
            }
        }

        static void initCallGraph() {
            if (callgraph == nullptr) {
                initPointerAnalysis();
                callgraph = pa->getPTACallGraph();
            }
        }

        static void initSVFG() {
            if (svfg == nullptr) {
                // Ensure pa is initialized.
                initPointerAnalysis();
                SVF::SVFGBuilder svfBuilder;
                svfg = svfBuilder.buildFullSVFG(pa);
            }
        }

        static bool traverseMemDependencies(const llvm::Value *src, std::set<const SVF::VFGNode*> &deps, const llvm::Value *trg = nullptr)
        {
            initSVFG();

            SVF::PAGNode* pNode = pag->getGNode(pag->getValueNode(src));
            const SVF::VFGNode* vNode = svfg->getDefVFGNode(pNode);
            SVF::FIFOWorkList<const SVF::VFGNode*> worklist;
            worklist.push(vNode);

            /// Traverse along SVFG
            while (!worklist.empty())
            {
                vNode = worklist.pop();

                if (trg != nullptr) {
                     if (trg == vNode->getValue()) {
                         return true;
                     }
                }

                // Chase uses
                for (auto it = vNode->OutEdgeBegin(), eit =
                        vNode->OutEdgeEnd(); it != eit; ++it)
                {
                    SVF::SVFGEdge* edge = *it;
                    SVF::SVFGNode* succNode = edge->getDstNode();
                    if (deps.find(succNode) == deps.end())
                    {
                        deps.insert(succNode);
                        worklist.push(succNode);
                    }
                }

                // Chase defs
                for (auto it = vNode->InEdgeBegin(), eit =
                        vNode->InEdgeEnd(); it != eit; ++it)
                {
                    SVF::VFGEdge* edge = *it;
                    SVF::VFGNode* predNode = edge->getSrcNode();
                    if (deps.find(predNode) == deps.end())
                    {
                        deps.insert(predNode);
                        worklist.push(predNode);
                    }
                }
            }

            return false;
        }
    };

}


#endif //VANGUARD_SVFUTILS_H
