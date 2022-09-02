//
// Created by Jon Stephens on 9/1/22.
//

#ifndef VANGUARD_BLOCKCHAINFACTORY_H
#define VANGUARD_BLOCKCHAINFACTORY_H

#include <program/UnitFactory.h>
#include <unordered_map>

namespace vanguard {
    class BlockchainFactory : public UnitFactory {
    public:
        BlockchainFactory() = default;

        Universe::CompilationUnit *createUnit(const llvm::Module *module) override;

        Universe::Function *createFn(const llvm::Function *function) override;

        Universe::Instruction *createIns(const llvm::Instruction *instruction) override;

        Universe::Block *createBlk(const llvm::BasicBlock *block) override;

        Type *createType(const llvm::Type *t) override;

        Value *createVal(const llvm::Value *val) override;

    private:

        std::unordered_map<const llvm::Module*, Universe::CompilationUnit*> moduleMap;
        std::unordered_map<const llvm::Function*, Universe::Function*> functionMap;
        std::unordered_map<const llvm::BasicBlock*, Universe::Block*> blockMap;
        std::unordered_map<const llvm::Instruction*, Universe::Instruction*> instructionMap;
        std::unordered_map<const llvm::Type*, Type*> typeMap;
        std::unordered_map<const llvm::Value*, Value*> valueMap;
    };
}



#endif //VANGUARD_BLOCKCHAINFACTORY_H
