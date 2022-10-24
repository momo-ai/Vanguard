//
// Created by Kostas Ferles on 9/15/22.
//

#ifndef VANGUARD_NEARMODEL_H
#define VANGUARD_NEARMODEL_H

#include "analysis/ir-utils/LLVMUtils.h"
#include "analysis/interproc-analysis/InterProceduralAnalyses.h"
#include "domain/libBlockchain/BlockchainModel.h"
#include "program/TypeClass.h"
#include "domain/libBlockchain/langs/rust/near/NearContract.h"

// TODO: Remove Domain template parameter
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
            assert(("Invalid pointer type" && dynamic_cast<PointerType<Domain> *>(selfVal->type())));

            return analysis::InterProceduralAnalyses<Domain>::writesMemTo(&ins, selfVal);
        }

        bool readsStorage(typename Domain::Instruction &ins) const override {
            auto insFun = ins.block()->function();

            auto selfVal = analysis::LLVMUtils<Domain>::getNamedFunctionArg(insFun, "self");

            if (selfVal == nullptr)
                selfVal = analysis::LLVMUtils<Domain>::getFunctionArg(insFun, 0);

            assert(("Could not find self argument" && selfVal != nullptr));
            assert(("Invalid pointer type" && dynamic_cast<PointerType<Domain> *>(selfVal->type())));

            return analysis::InterProceduralAnalyses<Domain>::readsMemFrom(&ins, selfVal);
        }

        CallResolver<Domain> *callResolver() const override {
            return nullptr;
        }

        bool isExternalCall(CallIns<Domain> &call) const override {
            auto trgs = call.targets();
            return std::any_of(trgs.begin(), trgs.end(), [](auto fun) -> bool {
                // TODO: WE NEED TO CHANGE THE DEFAULT BEHAVIOR OF CALLRESOLVER (IT CREATES BOGUS DOMAIN FUNCTIONS)
                if (auto contr = fun->contract()) {
                    return dynamic_cast<NearContract*>(contr)->isExternal();
                }
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

    private:

        static void replace_all(std::string &s, const std::string &toRepl, const std::string &replStr) {
            std::string buf;
            std::size_t pos = 0;
            std::size_t prevPos = 0;
            std::size_t toReplSize = toRepl.size();

            buf.reserve(s.size());

            while ((pos = s.find(toRepl, pos)) != std::string::npos) {
                buf.append(s, prevPos, pos - prevPos);
                buf += replStr;
                prevPos = (pos += toReplSize);
            }

            buf.append(s, prevPos, s.size() - prevPos);
            s.swap(buf);
        }

        static void fixDemangler(std::string &funcDemName) {
            replace_all(funcDemName, "$LT$", "<");
            replace_all(funcDemName, "$GT$", ">");
            replace_all(funcDemName, "..", "::");
            replace_all(funcDemName, "$u20$", " ");

            if (funcDemName[0] == '_')
                funcDemName.replace(0, 1, "");
        }

        static std::string clipRustHash(const std::string& funcName) {
            return funcName.substr(0, funcName.size() - 19);
        }

        // TODO: Move rest of the methods from old Near.cpp here.
    };

}


#endif //VANGUARD_NEARMODEL_H
