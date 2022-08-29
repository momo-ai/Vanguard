//
// Created by Jon Stephens on 3/23/22.
//

#include "domain/libBlockchain/include/Solidity/SolangModel.h"
#include "llvm/IR/Instructions.h"
#include "domain/libBlockchain/include/BlkElementaryType.h"
#include "domain/libBlockchain/include/BlkMapType.h"
#include "domain/libBlockchain/include/BlkUserType.h"
#include "domain/libBlockchain/include/BlkArrayType.h"
#include <regex>
#include <sstream>
#include <stdexcept>
#include "domain/libBlockchain/include/BlkTypeVisitor.h"

using namespace llvm;
using namespace std;

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
            result = t.blkName().substr(t.blkName().find_last_of(' ') + 1, t.blkName().length());
        }

        void visit(const BlkElementaryType &t) override {
            result = t.blkName();
        }
    };


    string getTypeString(const BlkType &type) {
        TypeTrans trans;
        type.accept(trans);
        return trans.result;
    }

    bool SolangModel::isTranslation(const BlkFunction &blockchainFn, vanguard::Function &fn) const {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        stringstream ss;
        ss << ".*" << blockchainFn.parent()->blkName() << "::";

        if(blockchainFn.isConstructor()) {
            ss << blockchainFn.blkName() << ".*";
        }
        else {
            //ss << "function::" << blockchainFn.name() ;
            ss << ".*" << blockchainFn.blkName() ;
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

    bool SolangModel::isAnyExternalCall(vanguard::Function &fn) const {
        return isCall(fn) || isStaticCall(fn) || isDelegateCall(fn);
    }

    bool SolangModel::isCall(vanguard::Function &fn) const {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        string name = llvmFn.getName().str();
        return name == "call";
    }

    bool SolangModel::isStaticCall(vanguard::Function &fn) const {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        string name = llvmFn.getName().str();
        return name == "callStatic";
    }

    bool SolangModel::isDelegateCall(vanguard::Function &fn) const {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        string name = llvmFn.getName().str();
        return name == "callDelegate";
    }

    bool SolangModel::writesVariable(const BlkVariable &var, vanguard::Instruction &ins) const {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(auto call = llvm::dyn_cast<CallInst>(&llvmIns)) {
            auto fn = call->getCalledFunction();
            stringstream ss;
            ss << ".*::function::v?__set_" << var.blkName() << ".*";
            std::regex reg(ss.str());

            if(fn->hasName() && regex_match(fn->getName().str(), reg)) {
                return true;
            }
        }

        return false;
    }

    bool SolangModel::readsVariable(const BlkVariable &var, vanguard::Instruction &ins) const {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(auto call = llvm::dyn_cast<CallInst>(&llvmIns)) {
            auto fn = call->getCalledFunction();
            stringstream ss;
            ss << ".*::function::v?__get_" << var.blkName() << ".*";
            std::regex reg(ss.str());

            if(fn->hasName() && regex_match(fn->getName().str(), reg)) {
                return true;
            }
        }

        return false;
    }

    bool SolangModel::writesStorage(vanguard::Function &fn) {
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

    bool SolangModel::readsStorage(vanguard::Function &fn) {
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