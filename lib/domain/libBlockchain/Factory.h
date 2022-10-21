//
// Created by Jon Stephens on 9/18/22.
//

#ifndef VANGUARD_LIBBLOCKCHAIN_FACTORY_H
#define VANGUARD_LIBBLOCKCHAIN_FACTORY_H

#include "Blockchain.h"
#include "BlockchainModel.h"
#include "SummaryReader.h"
#include "CompilationUnit.h"
#include "Contract.h"
#include "Function.h"
#include "Instruction.h"
#include "Type.h"
#include "Value.h"

namespace vanguard {
    template<typename Base, typename Domain>
    class Blockchain<Base, Domain>::Factory : public Base::Factory {
    public:
        typename Domain::Function *createBlkFn(const llvm::Module &module, BlockchainModel<Domain> &model, std::string contract,
                                               std::string name, std::string selector, bool isCnstr, Visibility vis, Mutability mut,
                                               std::vector<vanguard::Variable<Domain> *> params, std::vector<vanguard::Variable<Domain> *> rets, std::vector<std::string> mods) {
            auto fn = new typename Domain::Function(name, selector, isCnstr, vis, mut, std::move(params), std::move(rets), std::move(mods), nullptr);

            for(auto &llvmFn : module) {
                if(model.isImplementation(contract, *fn, llvmFn)) {
                    fn->wrap(&llvmFn);
                    this->functionMap[&llvmFn] = fn;
                    break;
                }
            }

            return fn;
        }

        typename Domain::Contract *createContract(const llvm::Module &module, BlockchainModel<Domain> &model, std::string& name, std::vector<typename Domain::Function *>& fns, std::vector<vanguard::Variable<Domain> *>& vars) {
            auto *contract = new typename Domain::Contract(model, name, fns, vars);
            return contract;
        }

        StructType<Domain> *createStruct(const llvm::Module &mod, BlockchainModel<Domain> &model, const std::string& name, std::vector<vanguard::Variable<Domain> *> fields) {
            auto *structType = new typename Domain::template BlkStructType<llvm::StructType>(std::move(fields), nullptr);
            return structType;
        }

        Variable<Domain> *createVariable(const llvm::Module &module, BlockchainModel<Domain> &model, std::string name, typename Domain::Type *type) {
            auto *var = new typename Domain::template BlkVariable<llvm::Value>(std::move(name), type, nullptr);
            return var;
        }

        ArrayType<Domain> *createArrayType(const llvm::Module &module, BlockchainModel<Domain> &model, std::string name, typename Domain::Type *base) {
            auto *arr = new typename Domain::template BlkArrayType<llvm::ArrayType>(base, nullptr);
            return arr;
        }

        MapType<Domain> *createMapType(const llvm::Module &module, BlockchainModel<Domain> &model, std::string name, typename Domain::Type *keyType, typename Domain::Type *valType) {
            auto *map = new typename Domain::template BlkMapType<llvm::Type>(keyType, valType, nullptr);
            return map;
        }

        typename Domain::CompilationUnit *createBlkUnit(const llvm::Module *module, const std::vector<typename Domain::Contract *> &contracts) {
            if(module == nullptr) {
                return nullptr;
            }

            if(this->moduleMap.find(module) == this->moduleMap.end()){
                this->moduleMap[module] = new typename Domain::CompilationUnit(contracts, module);
            }

            return this->moduleMap[module];
        }

    protected:


    };
}


#endif //VANGUARD_FACTORY_H
