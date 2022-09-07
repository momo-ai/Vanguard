//
// Created by Kostas Ferles on 8/31/22.
//

#ifndef VANGUARD_LLVMUTILS_H
#define VANGUARD_LLVMUTILS_H

#include <llvm/IR/Module.h>
#include <map>
#include <set>

#include "../../program/CompilationUnit.h"
#include "../../program/LLVMtoVanguard.h"
#include "../../detectors/DAWrapper.h"

namespace analysis {

    class LLVMUtils {
    public:

        static const std::map<llvm::Metadata::MetadataKind, std::vector<llvm::MDNode *>>& getMetadata(vanguard::CompilationUnit const *cUnit);

        static std::set<llvm::Metadata*> findNodesUnder(llvm::Metadata *root, std::function<bool(llvm::Metadata*)> &cond);

        static vanguard::Value* getFunctionArg(vanguard::Function *fun, int i);

        static const vanguard::Value* getNamedFunctionArg(vanguard::Function *fun, const std::string &name);

        static bool readsMemFrom(const vanguard::Instruction *instr, const vanguard::Value *obj);

        static bool writesMemTo(const vanguard::Instruction *instr, const vanguard::Value *obj);

        static const llvm::Value* isMemRead(const vanguard::Instruction *inst);

        static const llvm::Value* isMemWrite(const vanguard::Instruction *inst);

        static std::string demangleFunction(const vanguard::Function *fun);

    private:

        static std::map<llvm::Module const *, std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode*>>> mdnMap;

        static vanguard::LLVMtoVanguard *llvmToVanguard;
    };

} // analysis

#endif //VANGUARD_LLVMUTILS_H