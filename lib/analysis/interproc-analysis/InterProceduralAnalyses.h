//
// Created by Kostas Ferles on 10/10/22.
//

#ifndef VANGUARD_INTERPROCEDURALANALYSES_H
#define VANGUARD_INTERPROCEDURALANALYSES_H

#include <analysis/ir-utils/LLVMUtils.h>

#include "SVFUtils.h"

namespace analysis {
    template<typename Domain>
    class InterProceduralAnalyses {
    public:

        static bool readsMemFrom(const typename Domain::Instruction *instr, const typename Domain::Value *obj) {
            if (auto src = analysis::LLVMUtils<Domain>::isMemRead(instr))
                return analysis::SVFUtils::dependsOnTrg(*src, *obj->unwrap());
            return false;
        }

        static bool writesMemTo(const typename Domain::Instruction *instr, const typename Domain::Value *obj) {
            if (auto dest = analysis::LLVMUtils<Domain>::isMemWrite(instr))
                return analysis::SVFUtils::dependsOnTrg(*dest, *obj->unwrap());
            return false;
        }

        static bool valueDependsOn(const typename Domain::Value *src, const typename Domain::Instruction *instr) {
            return analysis::SVFUtils::dependsOnTrg(src->unwrap(), &instr->unwrap());
        }

        static std::vector<const typename Domain::Value*> getMemDeps(const typename Domain::Value *val) {
            auto &fact = Domain::Factory::instance();
            auto llvmDeps = analysis::SVFUtils::valueDeps(val->unwrap());

            std::vector<const typename Domain::Value*> rv;
            std::transform(llvmDeps.begin(), llvmDeps.end(), std::back_inserter(rv),
                           [&fact](auto llvmVal) { return fact.createVal(llvmVal); });
            return std::move(rv);
        }
    };
}

#endif //VANGUARD_INTERPROCEDURALANALYSES_H
