#include "LLVMUtils.h"

std::string analysis::printLLVMValue(const llvm::Value *v) {
    std::string s;
    llvm::raw_string_ostream sstr(s);
    v->print(sstr, false);
    return s;
}

void analysis::collectMedataForFunction(llvm::Function const *fun, std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode*>>& mdMap){
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

void analysis::createMetadataSlot(
    llvm::Module const *mod, llvm::MDNode *n,
    std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode *>> &mdMap) {

    auto &meta = mdMap[(llvm::MDNode::MetadataKind)n->getMetadataID()];
    if (std::find(meta.begin(), meta.end(), n) != meta.end())
        return;
    // the map also stores the number of each metadata node. It is the same
    // order as in the dumped bc file.
    meta.push_back(n);

    for (unsigned i = 0, e = n->getNumOperands(); i != e; ++i) {
        if (auto op = llvm::dyn_cast_or_null<llvm::MDNode>(n->getOperand(i))) {
            createMetadataSlot(mod, op, mdMap);
        }
    }
}
