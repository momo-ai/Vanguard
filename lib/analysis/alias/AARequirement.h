//
// Created by Jon Stephens on 8/22/22.
//

#ifndef VANGUARD_AAREQUIREMENT_H
#define VANGUARD_AAREQUIREMENT_H


#include "../Requirement.h"
#include "AAWrapper.h"

namespace vanguard {
    template<typename Domain>
    class AARequirement : public Requirement, public AAWrapper<Domain> {
    public:
        virtual void fetch(llvm::ModuleAnalysisManager &mam, llvm::FunctionAnalysisManager &fam) override {
            fnAnalysis = &fam;
        }
        llvm::AAResults *request(typename Domain::Function &reqFn) override {
            if(noAlias(reqFn)) {
                return nullptr;
            }

            if(this->curFn == &reqFn) {
                return this->fnAlias;
            }

            this->curFn = &reqFn;
            auto *fn = const_cast<llvm::Function *>(reqFn.unwrap());
            this->fnAlias = &fnAnalysis->getResult<llvm::AAManager>(*fn);

            return this->fnAlias;
        }
    private:
        llvm::FunctionAnalysisManager *fnAnalysis;
    };
}



#endif //VANGUARD_AAREQUIREMENT_H
