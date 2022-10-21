//
// Created by Kostas Ferles on 10/21/22.
//

#include "SummaryReader.h"

#include <utility>

#include "langs/solidity/SolidityFactory.h"
#include "langs/solidity/SolangModel.h"
#include "langs/rust/near/NearFactory.h"
#include "langs/rust/near/NearModel.h"

namespace vanguard {

    SummaryReader::SummaryReader(const llvm::Module &mod, const std::string& projectFile) : module(mod) {
        std::ifstream inStream(projectFile);
        rapidjson::IStreamWrapper jsonStream(inStream);
        std::cout << "starting" << std::endl;

        rapidjson::Document doc;
        doc.ParseStream(jsonStream);
        readSummary(doc);
    }

    void SummaryReader::readSummary(rapidjson::Value &val) {
        require(val.HasMember("compiler") && val["compiler"].IsString(), "Summary must declare compiler");
        require(val.HasMember("version") && val["version"].IsString(), "Summary must declare version");

        std::string compiler = val["compiler"].GetString();
        std::string version = val["version"].GetString();


        if(compiler == "Solang") {
            model = new SolangModel<BlockchainDomain>();
            langFactory = new SolidityFactory(BlockchainDomain::Factory::instance());
        }
        else if(compiler == "rustc") {

            require(val.HasMember("blockchain") && val["blockchain"].IsString(), "Missing blockchain for rustc compiler");
            std::string blockchainStr = val["blockchain"].GetString();

            if (blockchainStr == "near"){
                model = new NearModel<BlockchainDomain>();
                langFactory = new NearFactory(BlockchainDomain::Factory::instance());
            }
            else {
                error(std::string("Unknown blockchain for rustc"));
            }
        }
        else {
            error(std::string("Unknown compiler: ") + compiler);
        }

        // TODO: add back
        /*else if(compiler == "cargo-contract") {
            model = new InkModel(*alias);
        }
        else {
            error(string("Unknown compiler: ") + compiler);
        }*/

        if(val.HasMember("contracts")) {
            require(val["contracts"].IsArray(), "Summary contracts must be an array");
            for(rapidjson::Value &contractVal : val["contracts"].GetArray()) {
                foundContracts.push_back(readContract(contractVal));
            }
        }

        // TODO: Add back?
        /*for(auto &ref : storageRefs) {
            require(storageDecls.find(ref.second) != storageDecls.end(), string("Could not find referenced declaration for ") +
                                                                         ref.first->blkName());
            ref.first->setReferenced(storageDecls[ref.second]);
        }*/

        /*if(compiler == "Solang") {
            blockchain = new Solidity(llvmTrans, compiler, version, contracts);
        }
        else if(compiler == "cargo-contract") {
            blockchain = new Ink(llvmTrans, compiler, version, contracts, *alias);
        }

        return blockchain;*/
    }

    BlockchainDomain::Contract* SummaryReader::readContract(rapidjson::Value &val) {
        require(val.HasMember("id") && val["id"].IsNumber(), "Contract must have an id");
        require(val.HasMember("name") && val["name"].IsString(), "Contract must have a name");

        int id = val["id"].GetInt();
        std::string name = val["name"].GetString();

        // TODO: Add back
        /*vector<BlkUserType *> inherits = {};
        if(val.HasMember("inherits")) {
            require(val["inherits"].IsArray(), "contract inherits must be an array of UserType");

            for(rapidjson::Value &iVal : val["inherits"].GetArray()) {
                inherits.push_back(readUserType(iVal));
            }
        }

        vector<BlkEvent *> events = {};
        if(val.HasMember("events")) {
            require(val["events"].IsArray(), "Contract events must be an array of Function");

            for(rapidjson::Value &eVal : val["events"].GetArray()) {
                events.push_back(readEvent(eVal));
            }
        }*/

        std::vector<BlockchainDomain::Function *> functions = {};
        if(val.HasMember("functions")) {
            require(val["functions"].IsArray(), "Contract functions must be an array of Function");

            for(rapidjson::Value &fVal : val["functions"].GetArray()) {
                functions.push_back(readFunction(name, fVal));
            }
        }

        std::vector<Variable<BlockchainDomain> *> variables = {};
        if(val.HasMember("variables")) {
            require(val["variables"].IsArray(), "Contract variables must be an array of Variable");

            for(rapidjson::Value &vVal : val["variables"].GetArray()) {
                variables.push_back(readVariable(vVal));
            }
        }

        // TODO: Add back
        /*vector<BlkStruct *> structs = {};
        if(val.HasMember("structs")) {
            require(val["structs"].IsArray(), "Contract structs must be an array of Struct");
            for(rapidjson::Value &sVal : val["structs"].GetArray()) {
                structs.push_back(readStruct(sVal));
            }
        }

        vector<BlkEnum *> enums = {};
        if(val.HasMember("enums")) {
            require(val["enums"].IsArray(), "Contract enums must be an array of Enum");

            for(rapidjson::Value &eVal : val["enums"].GetArray()) {
                enums.push_back(readEnum(eVal));
            }
        }*/

        auto *contract = langFactory->createContract(module, *model, name, functions, variables);

        // TODO: Fix this temp hack: this is for NEAR contracts
        if (val.HasMember("external")) {
            require(val["external"].IsBool(), "external must be boolean");
            if (val["external"].GetBool())
                contract->setExternal();
        }

        //auto *contract = new Blockchain<Universe>::Contract(name, functions, variables);
        //storageDecls[id] = contract;
        return contract;
    }

    StructType<BlockchainDomain>* SummaryReader::readStruct(rapidjson::Value &val) {
        require(val.HasMember("id") && val["id"].IsNumber(), "Struct must have an id");
        require(val.HasMember("name") && val["name"].IsString(), "Struct must have a name");

        int id = val["id"].GetInt();
        std::string name = val["name"].GetString();

        std::vector<Variable<BlockchainDomain> *> fields = {};
        if(val.HasMember("fields")) {
            require(val["fields"].IsArray(), "Struct fields must be an array of Variable");

            for(auto &fVal : val["fields"].GetArray()) {
                fields.push_back(readVariable(fVal));
            }
        }

        auto *aStruct = langFactory->createStruct(module, *model, name, fields);


        // TODO: Add back?
        //storageDecls[id] = aStruct;
        return aStruct;
    }

    BlockchainDomain::Function* SummaryReader::readFunction(std::string contractName, rapidjson::Value &val) {
        require(val.HasMember("name") && val["name"].IsString(), "Function must have a name");
        require(val.HasMember("isConstructor") && val["isConstructor"].IsBool(), "Must identify if function is a constructor");
        require(val.HasMember("visibility") && val["visibility"].IsString(), "Function must have a visibility");
        require(val.HasMember("mutability") && val["mutability"].IsString(), "Function must have a mutability");

        std::string name = val["name"].GetString();
        bool isConstructor = val["isConstructor"].GetBool();
        Visibility visibility = langFactory->toVisibility(val["visibility"].GetString());
        Mutability mutability = langFactory->toMutability(val["mutability"].GetString());

        std::vector<Variable<BlockchainDomain>*> params = {};
        if(val.HasMember("params")) {
            require(val["params"].IsArray(), "Function params must be array of Variable");

            for(auto &pVal : val["params"].GetArray()) {
                params.push_back(readVariable(pVal));
            }
        }

        std::vector<Variable<BlockchainDomain>*> returns = {};
        if(val.HasMember("returns")) {
            require(val["returns"].IsArray(), "Function returns must be array of Variable");

            for(auto &rVal : val["returns"].GetArray()) {
                returns.push_back(readVariable(rVal));
            }
        }

        std::vector<std::string> modifiers = {};
        if(val.HasMember("modifiers")) {
            require(val["modifiers"].IsArray(), "Function modifiers must be array of string");

            for(auto &mVal : val["modifiers"].GetArray()) {
                require(mVal.IsString(), "Found modifier that isn't a string modifier");

                modifiers.emplace_back(mVal.GetString());
            }
        }
        std::string selector;
        if (rapidjson::Value::ConstMemberIterator selectorIt = val.FindMember("selector");
                selectorIt != val.MemberEnd()) {
            selector = selectorIt->value.GetString();
        }

        return langFactory->createBlkFn(module, *model, std::move(contractName), name, selector, isConstructor, visibility, mutability, params, returns, modifiers);
    }

    Variable<BlockchainDomain>* SummaryReader::readVariable(rapidjson::Value &val) {
        require(val.HasMember("type") && val["type"].IsObject(), "Variable must have a type");

        BlockchainDomain::Type *type = readType(val["type"]);

        std::string name = "";
        if(val.HasMember("name")) {
            require(val["name"].IsString(), "Variable name must be a string");
            name = val["name"].GetString();
        }

        return langFactory->createVariable(module, *model, name, type);
    }

    ArrayType<BlockchainDomain>* SummaryReader::readArrayType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        std::string subType = val["subType"].GetString();
        require(subType == "ArrayType");

        require(val.HasMember("name") && val["name"].IsString(), "ArrayType must have a name");
        require(val.HasMember("base"), "ArrayType must have a base type");
        auto base = readType(val["base"]);
        std::string name = val["name"].GetString();

        return langFactory->createArrayType(module, *model, name, base);
    }

    BlockchainDomain::Type* SummaryReader::readUserType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        std::string subType = val["subType"].GetString();
        require(subType == "UserType");

        require(val.HasMember("name") && val["name"].IsString(), "UserType must have a name");
        require(val.HasMember("refId") && val["refId"].IsNumber(), "UserType must have a reference id");

        std::string name = val["name"].GetString();
        uint id = val["refId"].GetUint();

        auto userType = langFactory->createBasicType(module, *model, name);

        // TODO: Add back?
        //storageRefs[userType] = id;

        return userType;
    }

    MapType<BlockchainDomain>* SummaryReader::readMapType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        std::string subType = val["subType"].GetString();
        require(subType == "MapType");

        require(val.HasMember("name") && val["name"].IsString(), "MapType must have a name");
        require(val.HasMember("key"), "MapType must have a key type");
        require(val.HasMember("value"), "MapType must have a value type");

        BlockchainDomain::Type *key = readType(val["key"]);
        BlockchainDomain::Type *value = readType(val["value"]);
        std::string name = val["name"].GetString();

        return langFactory->createMapType(module, *model, name, key, value);
    }

    BlockchainDomain::Type* SummaryReader::readElementaryType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        std::string subType = val["subType"].GetString();
        require(subType == "ElementaryType");

        require(val.HasMember("name") && val["name"].IsString(), "ElementaryType must have a name");
        std::string name = val["name"].GetString();

        return langFactory->createBasicType(module, *model, name);
    }

    BlockchainDomain::Type* SummaryReader::readType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        std::string subType = val["subType"].GetString();

        if(subType == "UserType") {
            return readUserType(val);
        }
        else if(subType == "ArrayType") {
            return readArrayType(val);
        }
        else if(subType == "MapType") {
            return readMapType(val);
        }
        else if(subType == "ElementaryType") {
            return readElementaryType(val);
        }

        error(std::string("Unknown Type: ") + subType);
        return nullptr;
    }
}