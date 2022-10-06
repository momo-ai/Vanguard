//
// Created by Kostas Ferles on 10/6/22.
//

#include "SVFUtils.h"

SVF::SVFModule * analysis::SVFUtils::svfModule = nullptr;

SVF::SVFIR * analysis::SVFUtils::pag = nullptr;

SVF::PointerAnalysis * analysis::SVFUtils::pa = nullptr;

SVF::PTACallGraph * analysis::SVFUtils::callgraph = nullptr;

SVF::VFG * analysis::SVFUtils::vfg = nullptr;