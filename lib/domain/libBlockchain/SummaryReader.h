//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_SUMMARYREADER_H
#define LIBBLOCKCHAIN_SUMMARYREADER_H

#include <string>
#include <map>
#include <llvm/IR/Module.h>

#include "domain/libBlockchain/BlockchainModel.h"
#include "program/Base.h"
#include "program/TypeClass.h"
#include "domain/Domains.h"
#include "rapidjson/document.h"

#include <fstream>
#include "rapidjson/istreamwrapper.h"
#include <stdexcept>
#include <iostream>

namespace vanguard {

    class LanguageFactory;

    class SummaryReader{
    public:

        SummaryReader(const llvm::Module &mod, const std::string& projectFile);

        //Blockchain *blockchain();
        [[nodiscard]] inline const std::vector<typename BlockchainDomain::Contract *>& contracts() const {
            return foundContracts;
        }

    private:

        const llvm::Module &module;

        BlockchainModel<BlockchainDomain> *model;

        LanguageFactory * langFactory;

        std::vector<BlockchainDomain::Contract *> foundContracts;

        // TODO: @Jon: do we need these?
        //std::map<int, BlkStorage *> storageDecls;
        //std::map<BlkUserType *, int> storageRefs;

        // TODO: Add back.
        //BlkEvent *readEvent(rapidjson::Value &val);

        inline void error(std::string msg) {
            throw std::runtime_error(msg);
        }

        inline void require(bool cond, std::string msg = "") {
            if(!cond) {
                error(msg);
            }
        }

        void readSummary(rapidjson::Value &val);

        BlockchainDomain::Contract *readContract(rapidjson::Value &val);

        StructType<BlockchainDomain>* readStruct(rapidjson::Value &val);

        // TODO: Add back
        /*BlkEnum *readEnum(rapidjson::Value &val);*/

        BlockchainDomain::Function *readFunction(std::string contractName, rapidjson::Value &val);

        Variable<BlockchainDomain> *readVariable(rapidjson::Value &val);

        BlockchainDomain::Type *readType(rapidjson::Value &val);

        ArrayType<BlockchainDomain> *readArrayType(rapidjson::Value &val);

        BlockchainDomain::Type *readUserType(rapidjson::Value &val);

        MapType<BlockchainDomain> *readMapType(rapidjson::Value &val);

        BlockchainDomain::Type *readElementaryType(rapidjson::Value &val);
    };
}



#endif //LIBBLOCKCHAIN_SUMMARYREADER_H
