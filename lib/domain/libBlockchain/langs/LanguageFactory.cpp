//
// Created by Kostas Ferles on 10/21/22.
//

#include "LanguageFactory.h"

namespace vanguard {

    BlockchainDomain::Function* LanguageFactory::createBlkFn(const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string contract,
                                                             std::string name, std::string selector, bool isCnstr, Visibility vis, Mutability mut,
                                                             std::vector<vanguard::Variable<BlockchainDomain> *> params,
                                                             std::vector<vanguard::Variable<BlockchainDomain> *> rets,
                                                             std::vector<std::string> mods) {
        return factory.createBlkFn(module, model, contract, name, selector, isCnstr, vis, mut, params, rets, mods);
    }

    BlockchainDomain::Contract* LanguageFactory::createContract(const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string &name,
                                                                std::vector<BlockchainDomain::Function *> &fns, std::vector<Variable<BlockchainDomain> *> &vars) {
        return factory.createContract(module, model, name, fns, vars);
    }

    StructType<BlockchainDomain>* LanguageFactory::createStruct(const llvm::Module &mod, BlockchainModel<BlockchainDomain> &model, const std::string &name,
                                                                std::vector<Variable<BlockchainDomain> *> fields) {
        return factory.createStruct(mod, model, name, fields);
    }

    Variable<BlockchainDomain>* LanguageFactory::createVariable(const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string name,
                                                                BlockchainDomain::Type *type) {
        return factory.createVariable(module, model, name, type);
    }

    ArrayType<BlockchainDomain>* LanguageFactory::createArrayType(const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string name,
                                                                  BlockchainDomain::Type *base) {
        return factory.createArrayType(module, model, name, base);
    }

    MapType<BlockchainDomain>* LanguageFactory::createMapType(const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string name,
                                                              BlockchainDomain::Type *keyType, BlockchainDomain::Type *valType) {
        return factory.createMapType(module, model, name, keyType, valType);
    }

    BlockchainDomain::CompilationUnit* LanguageFactory::createBlkUnit(const llvm::Module *module, const std::vector<BlockchainDomain::Contract *> &contracts) {
        return factory.createBlkUnit(module, contracts);
    }

}