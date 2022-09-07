//
// Created by Kostas Ferles on 8/31/22.
//

#ifndef VANGUARD_LLVMUTILS_H
#define VANGUARD_LLVMUTILS_H

#include <llvm/IR/Module.h>
#include <map>
#include <set>

#include "../../program/Universe.h"
#include "../../program/WrappedValue.h"
#include "../../program/UnitFactory.h"

namespace analysis {

    class LLVMUtils {
    public:

        static const std::map<llvm::Metadata::MetadataKind, std::vector<llvm::MDNode *>>& getMetadata(const vanguard::Universe::CompilationUnit *cUnit);

        static std::set<llvm::Metadata*> findNodesUnder(llvm::Metadata *root, std::function<bool(llvm::Metadata*)> &cond);

        static vanguard::Value* getFunctionArg(vanguard::Universe::Function *fun, int i);

        static const vanguard::Value* getNamedFunctionArg(vanguard::Universe::Function *fun, const std::string &name);

        template<typename Base, typename Wrap>
        static bool readsMemFrom(const vanguard::Universe::Instruction *instr, const vanguard::WrappedValue<Base, Wrap> *obj);

        template<typename Base, typename Wrap>
        static bool writesMemTo(const vanguard::Universe::Instruction *instr, const vanguard::WrappedValue<Base, Wrap> *obj);

        static const llvm::Value* isMemRead(const vanguard::Universe::Instruction *inst);

        static const llvm::Value* isMemWrite(const vanguard::Universe::Instruction *inst);

        static std::string demangleFunction(const vanguard::Universe::Function *fun);

    private:

        static std::map<llvm::Module const *, std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode*>>> mdnMap;

        static vanguard::UnitFactory *factory;
    };

} // analysis

#endif //VANGUARD_LLVMUTILS_H
