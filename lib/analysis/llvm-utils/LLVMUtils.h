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

#include "../../program/Universe.h"
#include "../../program/WrappedValue.h"
#include "../../program/UnitFactory.h"

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

        static void getPostDominatedBlocks(const vanguard::Universe::Block *block, llvm::SmallVector<vanguard::Universe::Block*> &dominated);

        static bool postDominates(const vanguard::Universe::Instruction *i1, const vanguard::Universe::Instruction *i2);

        template<typename Base, typename Wrap>
        static bool returnDependsOnVal(const vanguard::Universe::Function *fun, const vanguard::WrappedValue<Base, Wrap> *val);

        template<typename Base, typename Wrap>
        static bool valueDependsOn(const vanguard::WrappedValue<Base, Wrap> *src, const vanguard::Universe::Instruction *instr);

        static LocationInfo getLocInfo(const vanguard::Universe::Instruction *instr);

        static LocationInfo getLocInfo(const vanguard::Universe::Function *fun);

        template<typename Base, typename Wrap>
        static std::string print(const vanguard::WrappedValue<Base, Wrap> *val);

        static std::string print(const vanguard::Universe::Instruction *val);

    private:

        static std::map<const llvm::Function *, const llvm::PostDominatorTree*> postDomTrees;

        static std::map<llvm::Module const *, std::map<llvm::MDNode::MetadataKind, std::vector<llvm::MDNode*>>> mdnMap;

        static vanguard::UnitFactory *factory;

    private:
        static const llvm::PostDominatorTree* getPostDomTree(const llvm::Function *fun);
    };

} // analysis

#endif //VANGUARD_LLVMUTILS_H
