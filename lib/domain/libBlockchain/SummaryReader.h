//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_SUMMARYREADER_H
#define LIBBLOCKCHAIN_SUMMARYREADER_H

#include <string>
#include <map>
#include "Blockchain.h"
#include "BlockchainFactory.h"
#include "BlkValue.h"
#include "rapidjson/document.h"

namespace vanguard {
    class SummaryReader{
    public:
        SummaryReader(const llvm::Module &mod, const std::string& projectFile, BlockchainFactory *factory);
        //Blockchain *blockchain();
        std::vector<Blockchain<Universe>::Contract *> contracts() const;
    private:
        //std::map<int, BlkStorage *> storageDecls;
        //std::map<BlkUserType *, int> storageRefs;
        BlockchainModel *model;
        std::vector<Blockchain<Universe>::Contract *> foundContracts;
        BlockchainFactory *factory;
        const llvm::Module &module;
        //Blockchain *summary;
        //vanguard::AAWrapper *alias;

        //BlkEvent *readEvent(rapidjson::Value &val);
        void readSummary(rapidjson::Value &val);
        Blockchain<Universe>::Contract *readContract(rapidjson::Value &val);
        BlkStructType<StructType> *readStruct(rapidjson::Value &val);
        /*BlkEnum *readEnum(rapidjson::Value &val);*/
        Top<Blockchain<Universe>>::Function *readFunction(std::string contractName, rapidjson::Value &val);
        BlkVariable<Variable> *readVariable(rapidjson::Value &val);
        Type *readType(rapidjson::Value &val);
        ArrayType *readArrayType(rapidjson::Value &val);
        Type *readUserType(rapidjson::Value &val);
        MapType *readMapType(rapidjson::Value &val);
        Type *readElementaryType(rapidjson::Value &val);
    };
}



#endif //LIBBLOCKCHAIN_SUMMARYREADER_H
