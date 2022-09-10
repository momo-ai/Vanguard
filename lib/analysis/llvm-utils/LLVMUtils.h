//
// Created by Kostas Ferles on 8/31/22.
//

#ifndef VANGUARD_LLVMUTILS_H
#define VANGUARD_LLVMUTILS_H

#include <llvm/IR/Module.h>
#include <llvm/Analysis/PostDominators.h>
#include <map>
#include <set>
#include <utility>
#include <sstream>

#include "../../program/CompilationUnit.h"
#include "../../program/LLVMtoVanguard.h"
#include "../../detectors/DAWrapper.h"

namespace analysis {

    class LLVMUtils {
    public:

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

        static const std::map<llvm::Metadata::MetadataKind, std::vector<llvm::MDNode *>>& getMetadata(vanguard::CompilationUnit const *cUnit);

        static std::set<llvm::Metadata*> findNodesUnder(llvm::Metadata *root, std::function<bool(llvm::Metadata*)> &cond);

        static vanguard::Value* getFunctionArg(vanguard::Function *fun, int i);

        static const vanguard::Value* getNamedFunctionArg(vanguard::Function *fun, const std::string &name);

        static bool readsMemFrom(const vanguard::Instruction *instr, const vanguard::Value *obj);

        static bool writesMemTo(const vanguard::Instruction *instr, const vanguard::Value *obj);

        static const llvm::Value* isMemRead(const vanguard::Instruction *inst);

        static const llvm::Value* isMemWrite(const vanguard::Instruction *inst);

        static std::string demangleFunction(const vanguard::Function *fun);

        static void getPostDominatedBlocks(const vanguard::Block *block, llvm::SmallVector<vanguard::Block*> &dominated);

        static bool postDominates(const vanguard::Instruction *i1, const vanguard::Instruction *i2);

        static bool returnDependsOnVal(const vanguard::Function *fun, const vanguard::Instruction *val);

        static bool valueDependsOn(const vanguard::Value *src, const vanguard::Instruction *instr);

        static LocationInfo getLocInfo(const vanguard::Instruction *instr);

        static LocationInfo getLocInfo(const vanguard::Function *fun);

        static std::string print(const vanguard::Value *val);

        static std::string print(const vanguard::Instruction *val);

    private:

        static std::map<const llvm::Function *, const llvm::PostDominatorTree*> postDomTrees;

        static std::map<llvm::Module const *, std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode*>>> mdnMap;

        static vanguard::LLVMtoVanguard *llvmToVanguard;

    private:

        static const llvm::PostDominatorTree* getPostDomTree(const llvm::Function *fun);
    };

} // analysis

#endif //VANGUARD_LLVMUTILS_H
