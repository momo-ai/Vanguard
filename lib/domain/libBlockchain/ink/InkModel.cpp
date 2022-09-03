//
// Created by Jon Stephens on 4/10/22.
//

#include "domain/libBlockchain/include/Ink/InkModel.h"
#include "domain/libBlockchain/include/BlkElementaryType.h"
#include "domain/libBlockchain/include/BlkMapType.h"
#include "domain/libBlockchain/include/BlkUserType.h"
#include "domain/libBlockchain/include/BlkArrayType.h"
#include <regex>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include "domain/libBlockchain/include/BlkTypeVisitor.h"
#include "domain/libBlockchain/include/BlkContract.h"
#include "llvm/IR/Constants.h"
#include "program/Instruction.h"
#include "llvm/IR/Instructions.h"
#include <iostream>
#include "llvm/IR/IntrinsicInst.h"

using namespace std;

namespace blockchain {
    InkModel::InkModel(vanguard::AAWrapper &alias) : alias(alias) {}

    llvm::Value *InkModel::getSelfRef(const BlkFunction &blkFn, vanguard::Function &fn) {
        const llvm::Function& llvmFn = fn.unwrap();
        if(InkModel::isConstructorClosure(blkFn, fn)) {
            return llvmFn.getArg(llvmFn.arg_size() - 1);
        }

        return llvmFn.getArg(0);
    }

    llvm::MemoryLocation getContractVarLocation(const BlkContract &contract, const BlkVariable &var, vanguard::Instruction &ins) {
        const llvm::Instruction& llvmIns = ins.unwrap();
        const llvm::Function* fn = llvmIns.getFunction();
        auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
        vanguard::Function* fnV = llvmToVanguard.translateFunction(fn);

        auto blkFn = contract.findFunction(*fnV);
        if(blkFn == nullptr) {
            throw runtime_error("Should be contract function");
        }

        auto arg = InkModel::getSelfRef(*blkFn, *fnV);
        auto it = std::find(contract.variables().begin(), contract.variables().end(), &var);
        auto id = std::distance(contract.variables().begin(), it);

        if(!arg->getType()->isPointerTy()) {
            throw runtime_error("Should be pointer type");
        }

        auto argType = llvm::dyn_cast<llvm::PointerType>(arg->getType());
        if(!argType->getElementType()->isStructTy()) {
            throw runtime_error("Should be struct type");
        }
        auto structType = llvm::dyn_cast<llvm::StructType>(argType->getElementType());
        llvm::IntegerType *intType = llvm::IntegerType::get(llvmIns.getContext(), 32);
        llvm::Value* indexList[2] = {llvm::ConstantInt::get(intType, 0), llvm::ConstantInt::get(intType, id)};
        auto gep = llvm::GetElementPtrInst::Create(argType->getElementType(), arg, llvm::ArrayRef<llvm::Value*>(indexList, 2), "acc");
        auto &layout = fn->getParent()->getDataLayout();
        auto elementSize = layout.getTypeSizeInBits(structType->getElementType(id));
        //cout << elementSize << endl;
        //auto loc = MemoryLocation(gep, LocationSize::precise(elementSize));
        auto loc = llvm::MemoryLocation(gep, llvm::LocationSize::precise(1));
        return loc;
    }

    bool InkModel::isMemoryStore(vanguard::Instruction &ins) {
        const llvm::Instruction& llvmIns = ins.unwrap();
        return llvm::isa<llvm::StoreInst>(llvmIns) || llvm::isa<llvm::MemIntrinsic>(llvmIns);
    }

    bool InkModel::isMemoryRead(vanguard::Instruction &ins) {
        const llvm::Instruction& llvmIns = ins.unwrap();
        return llvm::isa<llvm::LoadInst>(llvmIns) || llvm::isa<llvm::MemTransferInst>(llvmIns);
    }

    llvm::MemoryLocation InkModel::getStoreLocation(vanguard::Instruction &ins) {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(auto store = llvm::dyn_cast<llvm::StoreInst>(&llvmIns)) {
            llvm::MemoryLocation storeLoc = llvm::MemoryLocation::get(store);
            return storeLoc;
        }
        else if(auto call = llvm::dyn_cast<llvm::MemIntrinsic>(&llvmIns)) {
            llvm::MemoryLocation storeLoc = llvm::MemoryLocation::getForDest(call);
            return storeLoc;
        }

        throw runtime_error("error");
    }

    llvm::MemoryLocation InkModel::getReadLocation(vanguard::Instruction &ins) {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(auto load = llvm::dyn_cast<llvm::LoadInst>(&llvmIns)) {
            llvm::MemoryLocation loadLoc = llvm::MemoryLocation::get(load);
            return loadLoc;
        }
        else if(auto call = llvm::dyn_cast<llvm::MemTransferInst>(&llvmIns)) {
            llvm::MemoryLocation loadLoc = llvm::MemoryLocation::getForSource(call);
            return loadLoc;
        }

        throw runtime_error("error");
    }

    bool InkModel::writesVariable(const BlkVariable &var, vanguard::Instruction &ins) const {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(isMemoryStore(ins)){
            llvm::MemoryLocation storeLoc = getStoreLocation(ins);

            if(auto contract = llvm::dyn_cast<BlkContract>(var.parent())) {
                //assuming no aliasing outside of contract functions.
                const llvm::Function* fn = llvmIns.getFunction();
                auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
                vanguard::Function* fnV = llvmToVanguard.translateFunction(fn);

                if(!contract->isContractFunction(*fnV)) {
                    return false;
                }
                llvm::MemoryLocation varLoc = getContractVarLocation(*contract, var, ins);

                auto aa = alias.request(*fnV);
                if(aa->alias(storeLoc, varLoc) > llvm::AliasResult::MayAlias) {
                    return true;
                }

                return false;
            }
            else {
                throw runtime_error("Only works for contract variables right now");
            }
        }
        if(auto call = llvm::dyn_cast<llvm::CallInst>(&llvmIns)) {
            auto calledFn = call->getCalledFunction();
            auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
            vanguard::Function* calledFnV = llvmToVanguard.translateFunction(calledFn);

            if(isLazyStore(*calledFnV)) {
                llvm::MemoryLocation loc = llvm::MemoryLocation::getBeforeOrAfter(call->getArgOperand(0));

                if (auto contract = llvm::dyn_cast<BlkContract>(var.parent())) {
                    //assuming no aliasing outside of contract functions.
                    const llvm::Function* fn = llvmIns.getFunction();
                    auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
                    vanguard::Function* fnV = llvmToVanguard.translateFunction(fn);

                    if (!contract->isContractFunction(*fnV)) {
                        return false;
                    }

                    llvm::MemoryLocation varLoc = getContractVarLocation(*contract, var, ins);
                    auto aa = alias.request(*fnV);
                    if (aa->alias(loc, varLoc) > llvm::AliasResult::MayAlias) {
                        return true;
                    }

                    return false;
                } else {
                    throw runtime_error("Only works for contract variables right now");
                }
            }
        }


        return false;
    }

    bool InkModel::readsVariable(const BlkVariable &var, vanguard::Instruction &ins) const {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(isMemoryRead(ins)) {
            llvm::MemoryLocation readLoc = getReadLocation(ins);

            if(auto contract = llvm::dyn_cast<BlkContract>(var.parent())) {
                //assuming no aliasing outside of contract functions.
                const llvm::Function* fn = llvmIns.getFunction();
                auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
                vanguard::Function* fnV = llvmToVanguard.translateFunction(fn);

                if(!contract->isContractFunction(*fnV)) {
                    return false;
                }

                llvm::MemoryLocation varLoc = getContractVarLocation(*contract, var, ins);
                auto aa = alias.request(*fnV);
                if(aa->alias(readLoc, varLoc) > llvm::AliasResult::MayAlias) {
                    return true;
                }

                return false;
            }
            else {
                throw runtime_error("Only works for contract variables right now");
            }
        }
        if(auto call = llvm::dyn_cast<llvm::CallInst>(&llvmIns)) {
            auto calledFn = call->getCalledFunction();
            auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
            vanguard::Function* calledFnV = llvmToVanguard.translateFunction(calledFn);

            if(isLazyGet(*calledFnV)) {
                llvm::MemoryLocation loc = llvm::MemoryLocation::getBeforeOrAfter(call->getArgOperand(0));

                if (auto contract = llvm::dyn_cast<BlkContract>(var.parent())) {
                    //assuming no aliasing outside of contract functions.
                    const llvm::Function* fn = llvmIns.getFunction();
                    auto& llvmToVanguard = vanguard::LLVMtoVanguard::getInstance();
                    vanguard::Function* fnV = llvmToVanguard.translateFunction(fn);

                    if (!contract->isContractFunction(*fnV)) {
                        return false;
                    }

                    llvm::MemoryLocation varLoc = getContractVarLocation(*contract, var, ins);
                    auto aa = alias.request(*fnV);
                    if (aa->alias(loc, varLoc) > llvm::AliasResult::MayAlias) {
                        return true;
                    }

                    return false;
                } else {
                    throw runtime_error("Only works for contract variables right now");
                }
            }
        }

        return false;
    }

    bool InkModel::isSelfDestruct(vanguard::Function &fn) {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        string fnName = llvmFn.getName().str();

        stringstream ss;
        ss << ".*ink_lang.*env_access.*EnvAccess.*terminate_contract[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        return regex_match(fnName, reg);
    }

    bool InkModel::isMsgSender(vanguard::Function &fn) {
        //_ZN8ink_lang10env_access18EnvAccess$LT$E$GT$6caller17h56520365e2893a15E
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        string fnName = llvmFn.getName().str();

        stringstream ss;
        ss << ".*ink_lang.*env_access.*EnvAccess.*caller[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        return regex_match(fnName, reg);
    }

    bool InkModel::isMsgValue(vanguard::Function &fn) {
        //ink_lang10env_access18EnvAccess$LT$E$GT$17transferred_value
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        string fnName = llvmFn.getName().str();

        stringstream ss;
        ss << ".*ink_lang.*env_access.*EnvAccess.*transferred_value[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        return regex_match(fnName, reg);
    }

    bool InkModel::isLazyGet(vanguard::Function &fn) {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        string fnName = llvmFn.getName().str();

        stringstream ss;
        ss << ".*ink_storage.*lazy.*Mapping.*get[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        return regex_match(fnName, reg);
    }

    bool InkModel::isLazyStore(vanguard::Function &fn) {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        string fnName = llvmFn.getName().str();

        stringstream ss;
        ss << ".*ink_storage.*lazy.*Mapping.*insert[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        return regex_match(fnName, reg);
    }

    bool InkModel::isConstructorClosure(const BlkFunction &blockchainFn, vanguard::Function &fn) {
        const llvm::Function& llvmFn = fn.unwrap();
        stringstream ss;
        ss << ".*\\.\\." << blockchainFn.parent()->blkName() << ".*" << blockchainFn.blkName() << ".*closure.*";
        std::regex reg(ss.str());
        string name = llvmFn.getName().str();
        return regex_match(llvmFn.getName().str(), reg);
    }

    // these fellas were originally declared as const because llvm uses const everywhere, so we wanted our stuff to be
    // compatible w the llvm required types so, remove all instances of vanguard::
    bool InkModel::isTranslation(const BlkFunction &blockchainFn, vanguard::Function &fn) const {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        if(blockchainFn.isConstructor() && isConstructorClosure(blockchainFn, fn)) {
            return true;
        }

        stringstream ss;
        ss << ".*\\.\\." << blockchainFn.parent()->blkName() << ".*" << blockchainFn.blkName() << "[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        string name = llvmFn.getName().str();
        return regex_match(llvmFn.getName().str(), reg);
    }

    bool InkModel::isAnyExternalCall(vanguard::Function &fn) const {
        return isCall(fn) || isStaticCall(fn) || isDelegateCall(fn);
    }

    bool InkModel::isCall(vanguard::Function &fn) const {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        //call::call_builder::CallBuilder
        stringstream ss;
        ss << ".*CallBuilder.*ink_env..call..call_builder..Call.*fire[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        return regex_match(llvmFn.getName().str(), reg);
    }

    bool InkModel::isStaticCall(vanguard::Function &fn) const {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        return false;
    }

    bool InkModel::isDelegateCall(vanguard::Function &fn) const {
        const llvm::Function& llvmFn = fn.unwrap();
        if(!llvmFn.hasName()) {
            return false;
        }

        stringstream ss;
        ss << ".*CallBuilder.*ink_env..call..call_builder..DelegateCall.*fire[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        return regex_match(llvmFn.getName().str(), reg);
    }
}