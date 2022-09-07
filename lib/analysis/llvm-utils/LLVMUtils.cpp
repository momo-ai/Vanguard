//
// Created by Kostas Ferles on 8/31/22.
//

#include <set>
#include <vector>
#include <llvm/Demangle/Demangle.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/IntrinsicInst.h>
#include <llvm/Analysis/AliasSetTracker.h>

#include "LLVMUtils.h"

namespace analysis {

    std::map<llvm::Module const *, std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode*>>> LLVMUtils::mdnMap;

    vanguard::LLVMtoVanguard *LLVMUtils::llvmToVanguard = &vanguard::LLVMtoVanguard::getInstance();

    // For debugging purposes.
    std::string printLLVMValue(const llvm::Value *v) {
        std::string s;
        llvm::raw_string_ostream sstr(s);
        v->print(sstr, false);
        return s;
    }

    // TODO: refine/fix this.
    // Does not consider any aliasing and over-approximates method calls.
    // I believe the cleanest way to make this more precise is to use MemorySSA
    // and augment the worklist with the memory defs.
    bool dependsOnValue(const llvm::Value *srcVal, const llvm::Value *destVal) {
        std::set<const llvm::Use*> visited;

        // TODO: switch to SmallVector
        std::vector<const llvm::Value*> toVisit;

        toVisit.push_back(srcVal);

        while (!toVisit.empty()) {
            auto currVal = toVisit.front();

            if (auto user = llvm::dyn_cast<llvm::User>(currVal)) {
                for (auto &use: user->operands()) {
                    auto useAsVal = llvm::dyn_cast<llvm::Value>(&use);
                    if (useAsVal && useAsVal == destVal)
                        return true;

                    if (visited.find(&use) != visited.end())
                        continue;

                    visited.insert(&use);

                    if (auto useAsUser = llvm::dyn_cast<llvm::User>(&use))
                        toVisit.push_back(useAsUser);
                }
            }

            toVisit.erase(toVisit.begin());
        }

        return false;
    }

    // The following two are logic extracted from legacy detectors, not used at the moment.
    llvm::MemoryLocation getReadLocation(const vanguard::Instruction& ins) {
        const llvm::Instruction& llvmIns = ins.unwrap();
        if(auto load = llvm::dyn_cast<llvm::LoadInst>(&llvmIns)) {
            llvm::MemoryLocation loadLoc = llvm::MemoryLocation::get(load);
            return loadLoc;
        }
        else if(auto call = llvm::dyn_cast<llvm::MemTransferInst>(&llvmIns)) {
            llvm::MemoryLocation loadLoc = llvm::MemoryLocation::getForSource(call);
            return loadLoc;
        }

        throw std::runtime_error("error");
    }

    llvm::MemoryLocation getWriteLocation(const vanguard::Instruction& instr) {
        const llvm::Instruction& llvmIns = instr.unwrap();
        if(auto store = llvm::dyn_cast<llvm::StoreInst>(&llvmIns)) {
            llvm::MemoryLocation storeLoc = llvm::MemoryLocation::get(store);
            return storeLoc;
        }
        else if(auto call = llvm::dyn_cast<llvm::MemIntrinsic>(&llvmIns)) {
            llvm::MemoryLocation storeLoc = llvm::MemoryLocation::getForDest(call);
            return storeLoc;
        }

        throw std::runtime_error("error");
    }

    void createMetadataSlot(llvm::Module const * mod, llvm::MDNode *n, std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode*>>& mdMap){

        auto &meta = mdMap[(llvm::MDNode::MetadataKind)n->getMetadataID()];
        if (std::find(meta.begin(), meta.end(), n) != meta.end())
            return;
        //the map also stores the number of each metadata node. It is the same order as in the dumped bc file.
        meta.push_back(n);

        for (unsigned i = 0, e = n->getNumOperands(); i!=e; ++i){
            if(auto op = dyn_cast_or_null<llvm::MDNode>(n->getOperand(i))){
                createMetadataSlot(mod, op, mdMap);
            }
        }
    }

    void collectMedataForFunction(llvm::Function const *fun, std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode*>>& mdMap){
        llvm::SmallVector<std::pair<unsigned, llvm::MDNode*>, 4> MDForInst;
        for(auto bb = fun->begin(), e = fun->end(); bb != e; ++bb) {
            for (const auto & inst : *bb) {
                // TODO: see if we need this
                //get the Metadata declared in the llvm intrinsic functions such as llvm.dbg.declare()
                // if(auto ci = llvm::dyn_cast<llvm::CallInst>(inst)){
                //    if(auto f = ci->getCalledFunction()){
                //        if(f->getName().startswith("llvm.")){
                //            for(unsigned i = 0, nop = inst->getNumOperands(); i != nop; ++i){
                //                if(auto n = llvm::dyn_cast_or_null<llvm::MDNode>(inst->getOperand(i))){
                //                    createMetadataSlot(N);
                //                }
                //            }
                //        }
                //    }
                // }

                //Get all the mdnodes attached to each instruction
                inst.getAllMetadata(MDForInst);
                for (unsigned i = 0, nMeta = MDForInst.size(); i != nMeta; ++i) {
                    createMetadataSlot(fun->getParent(), MDForInst[i].second, mdMap);
                }
                MDForInst.clear();
            }
        }
    }

    void findNodesHelper(llvm::Metadata *n, std::function<bool(llvm::Metadata*)> &cond, std::set<llvm::Metadata*> &visited, std::set<llvm::Metadata*> &found) {
        if (visited.find(n) != visited.end())
            return;

        visited.insert(n);

        if (cond(n))
            found.insert(n);

        if (auto nNode = llvm::dyn_cast<llvm::MDNode>(n)) {
            for (int i = 0; i < nNode->getNumOperands(); i++) {
                //for (auto &op: (nNode->operands())) {
                auto &op = nNode->getOperand(i);
                llvm::Metadata *meta = op.get();
                if (!meta)
                    continue;

                findNodesHelper(meta, cond, visited, found);
            }
        }
    }

    std::set<llvm::Metadata*> LLVMUtils::findNodesUnder(llvm::Metadata *root, std::function<bool(llvm::Metadata*)> &cond) {
        std::set<llvm::Metadata*> visited, found;
        findNodesHelper(root, cond, visited, found);
        return std::move(found);
    }

    std::map<llvm::Metadata::MetadataKind, std::vector<llvm::MDNode *>> const & LLVMUtils::getMetadata(vanguard::CompilationUnit const *cUnit) {

        auto &module = cUnit->unwrap();
        if (mdnMap.find(&module) == mdnMap.end()) {
            std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode*>> mdMap;

            for (auto &fun : module) {
                collectMedataForFunction(&fun, mdMap);
            }

            mdnMap[&module] = std::move(mdMap);
        }

        return mdnMap[&module];
    }

    vanguard::Value* LLVMUtils::getFunctionArg(vanguard::Function *fun, int i) {
        assert(("Invalid argument index.", i < fun->params().size()));

        return llvmToVanguard->translateValue(fun->unwrap().getArg(i));
    }

    const vanguard::Value* LLVMUtils::getNamedFunctionArg(vanguard::Function *fun, const std::string &name) {
        auto &llFun = fun->unwrap();

        for (auto &a : llFun.args()) {
            if (a.hasName() && a.getName() == name)
                return llvmToVanguard->translateValue(&a);
        }

        return nullptr;
    }

    const llvm::Value* LLVMUtils::isMemRead(vanguard::Instruction const * inst) {
        auto &llvmIns = inst->unwrap();

        if (auto loadInst = llvm::dyn_cast<llvm::LoadInst>(&llvmIns)) {
            return loadInst->getPointerOperand();
        }
        else if (auto memTrans = llvm::dyn_cast<llvm::MemTransferInst>(&llvmIns)) {
            return memTrans->getRawSource();
        }
        return nullptr;
    }

    const llvm::Value* LLVMUtils::isMemWrite(vanguard::Instruction const * inst) {
        auto &llvmIns = inst->unwrap();
        if (auto store = llvm::dyn_cast<llvm::StoreInst>(&llvmIns)) {
            return store->getPointerOperand();
        }
        else if (auto memIntr = llvm::dyn_cast<llvm::MemIntrinsic>(&llvmIns)) {
            return memIntr->getDest();
        }
        return nullptr;
    }

    bool LLVMUtils::readsMemFrom(const vanguard::Instruction * instr, const vanguard::Value * obj) {
        if (auto src = isMemRead(instr))
            return dependsOnValue(src, &obj->unwrap());
        return false;
    }

    bool LLVMUtils::writesMemTo(vanguard::Instruction const * instr, vanguard::Value const * obj) {
        if (auto dest = isMemWrite(instr))
            return dependsOnValue(dest, &obj->unwrap());
        return false;
    }

    std::string LLVMUtils::demangleFunction(const vanguard::Function *fun){
        auto &llvmFun = fun->unwrap();

        assert(("Function does not have name", llvmFun.hasName()));

        return llvm::demangle(llvmFun.getName().str());
    }
} // analysis