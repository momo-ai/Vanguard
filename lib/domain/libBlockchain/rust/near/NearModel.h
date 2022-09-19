//
// Created by Kostas Ferles on 9/15/22.
//

#ifndef VANGUARD_NEARMODEL_H
#define VANGUARD_NEARMODEL_H

#include <analysis/llvm-utils/LLVMUtils.h>
#include "../../BlockchainModel.h"

namespace vanguard {

    template <typename Domain>
    class NearModel : public BlockchainModel<Domain> {
    public:
        bool isImplementation(std::string contract, const typename Domain::Function &blockchainFn, const llvm::Function &llvmFn) const override {
            return NearModel::demangleRustName(llvmFn) == blockchainFn.name();
        }

        //bool isDelegateCall(const llvm::Function &llvmFn) override;

        bool isAnyLowLevelCall(CallIns<Domain> &call)  const override {
            return isLowLevelCall(call) || isLowLevelStaticCall(call) || isLowLevelDelegateCall(call);
        }

        bool isLowLevelCall(CallIns<Domain> &call) const override {
            throw std::runtime_error("To be implemented");
        }

        bool isLowLevelStaticCall(CallIns<Domain> &call) const override {
            throw std::runtime_error("Unsupported operation");
        }

        bool isLowLevelDelegateCall(CallIns<Domain> &call) const override {
            throw std::runtime_error("Unsupported operation");
        }

        bool writesStorage(typename Domain::Instruction &ins) const override {
            auto insFun = ins.block()->function();

            auto selfVal = analysis::LLVMUtils<Domain>::getNamedFunctionArg(insFun, "self");

            if (selfVal == nullptr)
                selfVal = analysis::LLVMUtils<Domain>::getFunctionArg(insFun, 0);

            assert(("Could not find self argument" && selfVal != nullptr));
            assert(("Invalid pointer type" && dynamic_cast<typename Domain::PointerType *>(selfVal->type())));

            return analysis::LLVMUtils<Domain>::writesMemTo(&ins, selfVal);
        }

        bool readsStorage(typename Domain::Instruction &ins) const override {
            auto insFun = ins.block()->function();

            auto selfVal = analysis::LLVMUtils<Domain>::getNamedFunctionArg(insFun, "self");

            if (selfVal == nullptr)
                selfVal = analysis::LLVMUtils<Domain>::getFunctionArg(insFun, 0);

            assert(("Could not find self argument" && selfVal != nullptr));
            assert(("Invalid pointer type" && dynamic_cast<typename Domain::PointerType *>(selfVal->type())));

            return analysis::LLVMUtils<Domain>::readsMemFrom(&ins, selfVal);
        }

        CallResolver<Domain> *callResolver() const override {

        }

        bool isExternalCall(CallIns<Domain> &call) const override {
            auto trgs = call.targets();
            return std::any_of(trgs.begin(), trgs.end(), [](auto fun) -> bool {
                // TODO: WE NEED TO CHANGE THE DEFAULT BEHAVIOR OF CALLRESOLVER (IT CREATES BOGUS DOMAIN FUNCTIONS)
                if (auto contr = fun->contract())
                    return contr->isExternal();
                return false;
            });
        }

        /*bool writesVariable(const BlkVariable &var, vanguard::Instruction &ins) const override;
        bool readsVariable(const BlkVariable &var, vanguard::Instruction &ins) const override;*/

        /*static bool writesStorage(vanguard::Function &fn);
        static bool readsStorage(vanguard::Function &fn);*/

        static std::string demangleRustName(const typename Domain::Function &fun) {
            auto llvmFun = fun.unwrap();
            assert(llvmFun && "Uninitialized Blockchain Function");

            return demangleRustName(*llvmFun);
        }

        static std::string demangleRustName(const llvm::Function &fun) {
            auto demangledName = clipRustHash(analysis::LLVMUtils<Domain>::demangleFunction(&fun));

            if (demangledName.find('$') != std::string::npos)
                fixDemangler(demangledName);

            return demangledName;
        }

        // TODO: Move rest of the methods from old Near.cpp here.
    };

}


#endif //VANGUARD_NEARMODEL_H
