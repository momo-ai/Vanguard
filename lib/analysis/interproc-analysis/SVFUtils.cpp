//
// Created by Kostas Ferles on 10/6/22.
//

#include "SVFUtils.h"

namespace analysis {
    SVF::SVFModule *SVFUtils::svfModule = nullptr;

    SVF::SVFIR *SVFUtils::pag = nullptr;

    SVF::BVDataPTAImpl *SVFUtils::pa = nullptr;

    SVF::PTACallGraph *SVFUtils::callgraph = nullptr;

    SVF::SVFG *SVFUtils::svfg = nullptr;

    std::map<const llvm::Value *, std::set<const SVF::VFGNode *>> SVFUtils::cachedDeps;

    bool SVFUtils::dependsOnTrg(const llvm::Value &src, const llvm::Value &trg) {
        if (cachedDeps.find(&src) == cachedDeps.end()) {
            std::set<const SVF::VFGNode *> deps;
            return traverseDependencies(&src, deps, &trg);
        } else {
            auto &deps = cachedDeps[&src];
            return std::any_of(deps.begin(), deps.end(), [&trg](auto node) { return node->getValue() == &trg; });
        }
    }

    std::vector<const llvm::Value*> SVFUtils::valueDeps(const llvm::Value *src) {
        if (cachedDeps.find(src) == cachedDeps.end()) {
            std::set<const SVF::VFGNode*> deps;
            traverseDependencies(src, deps);
            cachedDeps[src] = std::move(deps);
        }

        // Convert VFGNode -> llvm::Value
        std::vector<const llvm::Value*> valDeps;
        std::set<const SVF::VFGNode*> &memDeps = cachedDeps[src];
        std::transform(memDeps.begin(), memDeps.end(), std::back_inserter(valDeps),
                       [](auto mDep) { return mDep->getValue();});

        // Filter out null values
        valDeps.erase(std::remove_if(valDeps.begin(), valDeps.end(), [](auto val) { return val == nullptr;}),
                      valDeps.end());
        return std::move(valDeps);
    }

    void SVFUtils::initSVFModule() {
        if (svfModule == nullptr) {
            svfModule = SVF::LLVMModuleSet::getLLVMModuleSet()->getSVFModule();
        }
    }

    void SVFUtils::initPAG() {
        if (pag == nullptr) {
            initSVFModule();
            SVF::SVFIRBuilder builder;
            pag = builder.build(svfModule);
        }
    }

    void SVFUtils::initPointerAnalysis() {
        if (pa == nullptr) {
            initPAG();
            // TODO: make the following configurable
            pa = SVF::AndersenWaveDiff::createAndersenWaveDiff(pag);
        }
    }

    void SVFUtils::initCallGraph() {
        if (callgraph == nullptr) {
            initPointerAnalysis();
            callgraph = pa->getPTACallGraph();
        }
    }

    void SVFUtils::initSVFG() {
        if (svfg == nullptr) {
            // Ensure pa is initialized.
            initPointerAnalysis();
            SVF::SVFGBuilder svfBuilder;
            svfg = svfBuilder.buildFullSVFG(pa);
        }
    }

    bool SVFUtils::traverseDependencies(const llvm::Value *src, std::set<const SVF::VFGNode*> &deps, const llvm::Value *trg)
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
}