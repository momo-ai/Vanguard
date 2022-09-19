//
// Created by Kostas Ferles on 8/31/22.
//

#ifndef VANGUARD_LLVMUTILS_H
#define VANGUARD_LLVMUTILS_H

#include <llvm/IR/Module.h>
#include <llvm/Demangle/Demangle.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/IntrinsicInst.h>
#include <llvm/Analysis/PostDominators.h>
#include <map>
#include <set>
#include <utility>
#include <sstream>

#include <program/Universe.h>

namespace analysis {

    // For debugging purposes.
    static std::string printLLVMValue(const llvm::Value *v) {
        std::string s;
        llvm::raw_string_ostream sstr(s);
        v->print(sstr, false);
        return s;
    }

    // TODO: refine/fix this.
    // Does not consider any aliasing and over-approximates method calls.
    // I believe the cleanest way to make this more precise is to use MemorySSA
    // and augment the worklist with the memory defs.
    static bool dependsOnValue(const llvm::Value *srcVal, const llvm::Value *destVal) {
        std::set<const llvm::Use*> visited;

        // TODO: switch to SmallVector
        std::vector<const llvm::Value*> toVisit;

        toVisit.push_back(srcVal);

        while (!toVisit.empty()) {
            auto currVal = toVisit.front();

            if (currVal == destVal)
                return true;

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

    static void createMetadataSlot(llvm::Module const * mod, llvm::MDNode *n, std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode*>>& mdMap){

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

    static void collectMedataForFunction(llvm::Function const *fun, std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode*>>& mdMap){
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

    struct LocationInfo {
        std::string filename;

        int line;

        int column;

        LocationInfo(std::string filename, int line, int column)
                : filename(std::move(filename)), line(line), column(column) {

        }

        std::string toStr() {
            std::ostringstream ost;
            ost << filename;
            if (line != -1) ost << ":" << line;
            if (column != -1) ost << ":" << column;
            return ost.str();
        }
    };

    template<typename Domain>
    class LLVMUtils {
    public:

        static const std::map<llvm::Metadata::MetadataKind, std::vector<llvm::MDNode *>>& getMetadata(const typename Domain::CompilationUnit *cUnit) {
            auto module = cUnit->unwrap();
            if (mdnMap.find(module) == mdnMap.end()) {
                std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode*>> mdMap;

                for (auto &fun : *module) {
                    collectMedataForFunction(&fun, mdMap);
                }

                mdnMap[module] = std::move(mdMap);
            }

            return mdnMap[module];
        }

        static std::set<llvm::Metadata*> findNodesUnder(llvm::Metadata *root, std::function<bool(llvm::Metadata*)> &cond) {
            std::set<llvm::Metadata*> visited, found;
            findNodesHelper(root, cond, visited, found);
            return std::move(found);
        }

        static const typename Domain::Value* getFunctionArg(typename Domain::Function *fun, int i) {
            assert("Invalid argument index." && i < fun->params().size());

            return Domain::Factory::instance().createVal(fun->unwrap()->getArg(i));
        }

        static const typename Domain::Value* getNamedFunctionArg(typename Domain::Function *fun, const std::string &name) {
            auto llFun = fun->unwrap();
            auto &factory = Domain::Factory::instance();

            for (auto &a : llFun->args()) {
                if (a.hasName() && a.getName() == name)
                    return factory.createVal(&a);
            }

            return nullptr;
        }

        static bool readsMemFrom(const typename Domain::Instruction *instr, const typename Domain::Value *obj) {
            if (auto src = isMemRead(instr))
                return dependsOnValue(src, obj->unwrap());
            return false;
        }

        static bool writesMemTo(const typename Domain::Instruction *instr, const typename Domain::Value *obj) {
            if (auto dest = isMemWrite(instr))
                return dependsOnValue(dest, obj->unwrap());
            return false;
        }

        static const llvm::Value* isMemRead(const typename Domain::Instruction *inst) {
            const auto llvmIns = inst->unwrap();

            if (auto loadInst = llvm::dyn_cast<llvm::LoadInst>(llvmIns)) {
                return loadInst->getPointerOperand();
            }
            else if (auto memTrans = llvm::dyn_cast<llvm::MemTransferInst>(llvmIns)) {
                return memTrans->getRawSource();
            }
            return nullptr;
        }

        static const llvm::Value* isMemWrite(const typename Domain::Instruction *inst) {
            const auto llvmIns = inst->unwrap();
            if (auto store = llvm::dyn_cast<llvm::StoreInst>(llvmIns)) {
                return store->getPointerOperand();
            }
            else if (auto memIntr = llvm::dyn_cast<llvm::MemIntrinsic>(llvmIns)) {
                return memIntr->getDest();
            }
            return nullptr;
        }

        static std::string demangleFunction(const llvm::Function *fun) {
            assert("Function does not have name" && fun->hasName());

            return llvm::demangle(fun->getName().str());
        }

        static void getPostDominatedBlocks(const typename Domain::Block *block, llvm::SmallVector<typename Domain::Block*> &dominated) {
            auto llvmBlock = block->unwrap();
            auto domTree = getPostDomTree(llvmBlock->getParent());
            llvm::SmallVector<llvm::BasicBlock*> descendants;
            domTree->getDescendants(const_cast<llvm::BasicBlock*>(llvmBlock), descendants);

            auto &factory = Domain::Factory::instance();
            for (auto & descendant : descendants)
                dominated.push_back(factory.createBlk(descendant));
        }

        static bool postDominates(const typename Domain::Instruction *i1, const typename Domain::Instruction *i2) {
            auto i1BB = i1->block(), i2BB = i2->block();

            assert(i1BB->function() == i2BB->function() && "Invalid instructions: i1 & i2 must belong to the same function");
            auto domTree = getPostDomTree(i1BB->function()->unwrap());

            auto llvmI1 = i1->unwrap(), llvmI2 = i2->unwrap();
            if (i1->block() == i2->block()) return domTree->dominates(llvmI1, llvmI2);
            else return domTree->dominates(llvmI1->getParent(), llvmI2->getParent());
        }

        static bool returnDependsOnVal(const typename Domain::Function *fun, const typename Domain::Value *val) {
            auto llvmFun = fun->unwrap();

            llvm::SmallVector<const llvm::Value*> rvs;
            for (auto &bb : *llvmFun)
                for (auto &inst : bb)
                    if (auto retInst = llvm::dyn_cast<llvm::ReturnInst>(&inst))
                        if (auto retVal = retInst->getReturnValue())
                            rvs.push_back(retVal);

            return llvm::any_of(rvs, [&val](const llvm::Value *retVal) -> bool {return dependsOnValue(retVal, val->unwrap()); });
        }

        static bool valueDependsOn(const typename Domain::Value *src, const typename Domain::Instruction *instr) {
            return dependsOnValue(src->unwrap(), &instr->unwrap());
        }

        static LocationInfo getLocInfo(const typename Domain::Instruction *instr) {
            auto &llvmInstr = instr->unwrap();
            auto &dbLoc = llvmInstr.getDebugLoc();
            return {dbLoc->getFilename().str(), static_cast<int>(dbLoc->getLine()), static_cast<int>(dbLoc->getColumn())};
        }

        static LocationInfo getLocInfo(const typename Domain::Function *fun) {
            auto llvmFun = fun->unwrap();
            llvm::SmallVector<std::pair<unsigned int, llvm::MDNode*>> metadata;
            llvmFun->getAllMetadata(metadata);
            for (auto md : metadata) {
                if (auto diSub = llvm::dyn_cast<llvm::DISubprogram>(metadata[0].second)) {
                    return {diSub->getFilename().str(), static_cast<int>(diSub->getLine()), -1};
                }
            }
            return {"Unknown Location", -1, -1};
        }

        static std::string print(const typename Domain::Value *val) {
            return printLLVMValue(&val->unwrap());
        }

        static std::string print(const typename Domain::Instruction *val) {
            return printLLVMValue(&val->unwrap());
        }

    private:

        static std::map<const llvm::Function *, const llvm::PostDominatorTree*> postDomTrees;

        static std::map<llvm::Module const *, std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode*>>> mdnMap;

    private:
        static const llvm::PostDominatorTree* getPostDomTree(const llvm::Function *fun) {
            if (postDomTrees.find(fun) == postDomTrees.end()) {
                postDomTrees[fun] = new llvm::PostDominatorTree(const_cast<llvm::Function&>(*fun));
            }

            return postDomTrees[fun];
        }

        static void findNodesHelper(llvm::Metadata *n, std::function<bool(llvm::Metadata*)> &cond, std::set<llvm::Metadata*> &visited, std::set<llvm::Metadata*> &found) {
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
    };


    template<typename Domain>
    std::map<const llvm::Function *, const llvm::PostDominatorTree*> LLVMUtils<Domain>::postDomTrees;

    template<typename Domain>
    std::map<llvm::Module const *, std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode*>>> LLVMUtils<Domain>::mdnMap;


} // analysis

#endif //VANGUARD_LLVMUTILS_H