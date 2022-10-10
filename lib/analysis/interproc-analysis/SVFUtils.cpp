//
// Created by Kostas Ferles on 10/6/22.
//

#include "SVFUtils.h"

SVF::SVFModule * analysis::SVFUtils::svfModule = nullptr;

SVF::SVFIR * analysis::SVFUtils::pag = nullptr;

SVF::BVDataPTAImpl * analysis::SVFUtils::pa = nullptr;

SVF::PTACallGraph * analysis::SVFUtils::callgraph = nullptr;

SVF::SVFG * analysis::SVFUtils::svfg = nullptr;

std::map<const llvm::Value*, std::set<const SVF::VFGNode*>> analysis::SVFUtils::cachedDeps;