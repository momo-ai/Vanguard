//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_SOLANGTOLLVM_H
#define LIBBLOCKCHAIN_SOLANGTOLLVM_H

#include "../BlockchainModel.h"
#include "llvm/IR/Function.h"
#include <sstream>
#include <regex>
#include <program/TypeClass.h>

namespace vanguard {
    template<typename Domain>
    class SolangModel : public BlockchainModel<Domain> {
    public:
        bool isImplementation(std::string contract, const typename Domain::Function &blockchainFn, const llvm::Function &llvmFn) const override {
            if(!llvmFn.hasName()) {
                return false;
            }

            std::stringstream ss;
            ss << ".*" << contract << "::";

            if(blockchainFn.isConstructor()) {
                ss << blockchainFn.name() << ".*";
            }
            else {
                //ss << "function::" << blockchainFn.name() ;
                ss << ".*" << blockchainFn.name() ;
                if(!blockchainFn.params().empty() || !blockchainFn.modifiers().empty()) {
                    ss << "__";
                }

                for(auto var : blockchainFn.params()) {
                  ss << ".*";

                  // FIXME: llvm value is null at this point
                  // ss << getTypeString(var->type()) << ".*";
                }

                for(auto &modifier : blockchainFn.modifiers()) {
                    ss << modifier << ".*";
                }

                ss << "$";
            }

            std::regex reg(ss.str());
            return regex_match(llvmFn.getName().str(), reg);
        }
        //bool isExternalCall(const llvm::Function &llvmFn) override;
        //bool isDelegateCall(const llvm::Function &llvmFn) override;
        bool isAnyLowLevelCall(CallIns<Domain> &call) const override {
            return isLowLevelCall(call) || isLowLevelStaticCall(call) || isLowLevelDelegateCall(call);
        }

        bool isLowLevelCall(CallIns<Domain> &call) const override {
            for(auto tgt : call.targets()) {
                if(tgt->name() == "call") {
                    return true;
                }
            }

            return false;
        }

        bool isLowLevelStaticCall(CallIns<Domain> &call) const override {
            for(auto tgt : call.targets()) {
                if(tgt->name() == "callStatic") {
                    return true;
                }
            }

            return false;
        }

        bool isLowLevelDelegateCall(CallIns<Domain> &call) const override {
            for(auto tgt : call.targets()) {
                if(tgt->name() == "callDelegate") {
                    return true;
                }
            }

            return false;
        }

        bool writesStorage(typename Domain::Instruction &ins) const override {
            CallTargetResolver tgtResolver;
            ins.accept(tgtResolver);

            if(tgtResolver.tgts.empty()) {
                return false;
            }

            std::stringstream ss;
            ss << ".*::function::" << "v?__set_.*";

            return std::any_of(tgtResolver.tgts.begin(), tgtResolver.tgts.end(), [&ss](auto fn){std::regex reg(ss.str()); return regex_match(fn->name(), reg);});
        }
        bool readsStorage(typename Domain::Instruction &ins) const override {
            CallTargetResolver tgtResolver;
            ins.accept(tgtResolver);

            if(tgtResolver.tgts.empty()) {
                return false;
            }

            std::stringstream ss;
            ss << ".*::function::" << "v?__get_.*";

            return std::any_of(tgtResolver.tgts.begin(), tgtResolver.tgts.end(), [&ss](auto fn){std::regex reg(ss.str()); return regex_match(fn->name(), reg);});
        }

        CallResolver<Domain> *callResolver() const override {
            return nullptr;
        }

        bool isExternalCall(CallIns<Domain> &call) const override {
            throw std::runtime_error("To be implemented");
        }

        /*bool writesVariable(const BlkVariable &var, vanguard::Instruction &ins) const override;
        bool readsVariable(const BlkVariable &var, vanguard::Instruction &ins) const override;*/

        /*static bool writesStorage(vanguard::Function &fn);
        static bool readsStorage(vanguard::Function &fn);*/
    private:
        class CallTargetResolver : public InstructionClassVisitor<Domain> {
            public:
            std::vector<typename Domain::Function *> tgts;
            void visit(const CallIns<Domain> &v) override{
                    tgts = v.targets();
            }
        };

        class TypeTrans : public TypeVisitor<Domain> {
        public:
            std::string result;
            void visit(const ArrayType<Domain> &t) override {
                t.baseType()->accept(*this);
                result += ":";
            }

            void visit(const MapType<Domain> &t) override {
                std::string oldResult = result;
                result = "";
                t.keyType()->accept(*this);
                std::string keyType = result;
                result = "";
                t.valueType()->accept(*this);
                std::string valType = result;

                std::stringstream namestream;
                namestream << oldResult
                           << "mapping:"
                           << keyType << ":"
                           << valType;
                result = namestream.str();
            }

            void visit(const ObjectType<Domain> &t) override {
                result = t.name().substr(t.name().find_last_of(' ') + 1, t.name().length());
            }

            void commonVisit(const typename Domain::Type &t) override {
                result = t.name();
            }
        };

        std::string getTypeString(const typename Domain::Type *type) const {
            TypeTrans trans;
            type->accept(trans);
            return trans.result;
        }
    };
}



#endif //LIBBLOCKCHAIN_SOLANGTOLLVM_H
