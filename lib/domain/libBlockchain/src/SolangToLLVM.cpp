//
// Created by Jon Stephens on 3/23/22.
//

#include "../include/SolangToLLVM.h"
#include "llvm/IR/Instructions.h"
#include "../include/BlkElementaryType.h"
#include "../include/BlkMapType.h"
#include "../include/BlkUserType.h"
#include "../include/BlkArrayType.h"
#include <regex>
#include <sstream>
#include <stdexcept>
#include "../include/BlkTypeVisitor.h"

using namespace llvm;

namespace blockchain {
    class TypeTrans : public BlkTypeVisitor {
    public:
        string result;
        void visit(const BlkArrayType &t) override {
            t.base().accept(*this);
            result += ":";
        }

        void visit(const BlkMapType &t) override {
            t.key().accept(*this);
            string keyType = result;
            result = "";
            t.value().accept(*this);
            string valType = result;

            stringstream namestream;
            namestream << "mapping:"
                       << keyType << ":"
                       << valType;
            result = namestream.str();
        }

        void visit(const BlkUserType &t) override {
            result = t.name().substr(t.name().find_last_of(' ') + 1,  t.name().length());
        }

        void visit(const BlkElementaryType &t) override {
            result = t.name();
        }
    };


    string getTypeString(const BlkType &type) {
        TypeTrans trans;
        type.accept(trans);
        return trans.result;
    }

    bool SolangToLLVM::isTranslation(const BlkFunction &blockchainFn, vanguard::Function &fn) const {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        stringstream ss;
        ss << ".*" << blockchainFn.parent()->name() << "::";

        if(blockchainFn.isConstructor()) {
            ss << blockchainFn.name() << ".*";
        }
        else {
            //ss << "function::" << blockchainFn.name() ;
            ss << ".*" << blockchainFn.name() ;
            if(!blockchainFn.parameters().empty() || !blockchainFn.modifiers().empty()) {
                ss << "__";
            }

            for(auto var : blockchainFn.parameters()) {
                ss << getTypeString(var->varType()) << ".*";
            }

            for(auto &modifier : blockchainFn.modifiers()) {
                ss << modifier << ".*";
            }

            ss << "$";
        }

        std::regex reg(ss.str());
        return regex_match(llvmFn.getName().str(), reg);
    }

    bool SolangToLLVM::isAnyExternalCall(vanguard::Function &fn) const {
        return isCall(fn) || isStaticCall(fn) || isDelegateCall(fn);
    }

    bool SolangToLLVM::isCall(vanguard::Function &fn) const {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        return llvmFn.getName().str() == "call";
    }

    bool SolangToLLVM::isStaticCall(vanguard::Function &fn) const {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        return llvmFn.getName().str() == "callStatic";
    }

    bool SolangToLLVM::isDelegateCall(vanguard::Function &fn) const {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        return llvmFn.getName().str() == "callDelegate";
    }

    bool SolangToLLVM::writesVariable(const BlkVariable &var, vanguard::Instruction &ins) const {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(auto call = llvm::dyn_cast<CallInst>(&llvmIns)) {
            auto fn = call->getCalledFunction();
            stringstream ss;
            ss << ".*::function::v?__set_" << var.name() << ".*";
            std::regex reg(ss.str());

            if(fn->hasName() && regex_match(fn->getName().str(), reg)) {
                return true;
            }
        }

        return false;
    }

    bool SolangToLLVM::readsVariable(const BlkVariable &var, vanguard::Instruction &ins) const {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(auto call = llvm::dyn_cast<CallInst>(&llvmIns)) {
            auto fn = call->getCalledFunction();
            stringstream ss;
            ss << ".*::function::v?__get_" << var.name() << ".*";
            std::regex reg(ss.str());

            if(fn->hasName() && regex_match(fn->getName().str(), reg)) {
                return true;
            }
        }

        return false;
    }

    bool SolangToLLVM::writesStorage(vanguard::Function &fn) {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        string fnName = llvmFn.getName().str();

        stringstream ss;
        ss << ".*::function::" << "v?__set_.*";

        std::regex reg(ss.str());
        return regex_match(fnName, reg);
    }

    bool SolangToLLVM::readsStorage(vanguard::Function &fn) {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        string fnName = llvmFn.getName().str();

        stringstream ss;
        ss << ".*::function::" << "v?__get_.*";

        std::regex reg(ss.str());
        return regex_match(fnName, reg);
    }
}