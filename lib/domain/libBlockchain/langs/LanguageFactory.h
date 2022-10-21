//
// Created by Kostas Ferles on 10/21/22.
//

#ifndef VANGUARD_LANGUAGEFACTORY_H
#define VANGUARD_LANGUAGEFACTORY_H

#include "program/Factory.h"

#include "domain/Domains.h"
#include "domain/libBlockchain/Factory.h"

namespace vanguard {

    class LanguageFactory {
    public:

        inline explicit LanguageFactory(BlockchainDomain::Factory &factory) : factory(factory) { }

        virtual BlockchainDomain::Type *createBasicType(rapidjson::Value &val, const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string name) = 0;

        virtual Visibility toVisibility(const std::string& visStr) = 0;

        virtual Mutability toMutability(const std::string& mutStr) = 0;

        // TODO: Reduce number of arguments in the below methods.

        virtual BlockchainDomain::Function *createBlkFn(rapidjson::Value &val, const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string contract,
                                                        std::string name, std::string selector, bool isCnstr, Visibility vis, Mutability mut,
                                                        std::vector<vanguard::Variable<BlockchainDomain> *> params, std::vector<vanguard::Variable<BlockchainDomain> *> rets,
                                                        std::vector<std::string> mods);

        virtual BlockchainDomain::Contract *createContract(rapidjson::Value &val, const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string& name,
                                                           std::vector<BlockchainDomain::Function *>& fns, std::vector<Variable<BlockchainDomain> *>& vars);

        virtual StructType<BlockchainDomain> *createStruct(rapidjson::Value &val, const llvm::Module &mod, BlockchainModel<BlockchainDomain> &model, const std::string& name, std::vector<Variable<BlockchainDomain> *> fields);

        virtual Variable<BlockchainDomain> *createVariable(rapidjson::Value &val, const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string name, BlockchainDomain::Type *type);

        virtual ArrayType<BlockchainDomain> *createArrayType(rapidjson::Value &val, const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string name, BlockchainDomain::Type *base);

        virtual MapType<BlockchainDomain> *createMapType(rapidjson::Value &val, const llvm::Module &module, BlockchainModel<BlockchainDomain> &model, std::string name, BlockchainDomain::Type *keyType, BlockchainDomain::Type *valType);

        virtual BlockchainDomain::CompilationUnit *createBlkUnit(rapidjson::Value &val, const llvm::Module *module, const std::vector<BlockchainDomain::Contract *> &contracts);

    protected:

        inline void require(bool cond, std::string msg = "") {
            if(!cond) {
                throw std::runtime_error(msg);
            }
        }

    private:

        BlockchainDomain::Factory &factory;
    };

}


#endif //VANGUARD_LANGUAGEFACTORY_H
