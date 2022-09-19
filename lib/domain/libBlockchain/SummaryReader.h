//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_SUMMARYREADER_H
#define LIBBLOCKCHAIN_SUMMARYREADER_H

#include <string>
#include <map>
#include "Blockchain.h"
#include "rapidjson/document.h"

#include <fstream>
#include "rapidjson/istreamwrapper.h"
#include <stdexcept>
#include <iostream>

#include "solidity/SolangModel.h"

namespace vanguard {
    template<typename Domain>
    class SummaryReader{
    public:
        SummaryReader(const llvm::Module &mod, const std::string& projectFile) : module(mod) {
            model = nullptr;
            std::ifstream inStream(projectFile);
            rapidjson::IStreamWrapper jsonStream(inStream);
            std::cout << "starting" << std::endl;

            rapidjson::Document doc;
            doc.ParseStream(jsonStream);
            readSummary(doc);
        }

        //Blockchain *blockchain();
        std::vector<typename Domain::Contract *> contracts() const {
            return foundContracts;
        }

    private:
        //std::map<int, BlkStorage *> storageDecls;
        //std::map<BlkUserType *, int> storageRefs;
        BlockchainModel<Domain> *model;
        std::vector<typename Domain::Contract *> foundContracts;
        const llvm::Module &module;
        //Blockchain *summary;
        //vanguard::AAWrapper *alias;

        //BlkEvent *readEvent(rapidjson::Value &val);

        Visibility toVisibility(const std::string& visStr) {
            if(visStr == "external") { return EXTERNAL; }
            if(visStr == "public") { return PUBLIC; }
            if(visStr == "internal") { return INTERNAL; }
            if(visStr == "private") { return PRIVATE; }

            throw std::runtime_error("Unknown visibility " + visStr);
        }

        Mutability toMutability(const std::string& mutStr) {
            if(mutStr == "pure") { return PURE; }
            if(mutStr == "view") { return VIEW; }
            if(mutStr == "payable") { return PAYABLE; }
            if(mutStr == "nonpayable") { return NONPAYABLE; }

            throw std::runtime_error("Unknown mutability " + mutStr);
        }

        void error(std::string msg) {
            throw std::runtime_error(msg);
        }

        void require(bool cond, std::string msg = "") {
            if(!cond) {
                error(msg);
            }
        }

        void readSummary(rapidjson::Value &val) {
            require(val.HasMember("compiler") && val["compiler"].IsString(), "Summary must declare compiler");
            require(val.HasMember("version") && val["version"].IsString(), "Summary must declare version");

            std::string compiler = val["compiler"].GetString();
            std::string version = val["version"].GetString();

            //Blockchain *blockchain;
            //vector<Blockchain<Universe>::Contract *> contracts = {};

            if(compiler == "Solang") {
                model = new SolangModel<Domain>();
            }
            else if(compiler == "rustc") {
                require(val.HasMember("blockchain") && val["blockchain"].IsString(), "Missing blockchain for rustc compiler");
                std::string blockchainStr = val["blockchain"].GetString();
                if (blockchainStr == "near"){
                    model = new NearModel<Domain>();
                }
                else {
                    error(std::string("Unknown blockchain for rustc"));
                }
            }
            else {
                error(std::string("Unknown compiler: ") + compiler);
            }
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

        typename Domain::Contract *readContract(rapidjson::Value &val) {
            require(val.HasMember("id") && val["id"].IsNumber(), "Contract must have an id");
            require(val.HasMember("name") && val["name"].IsString(), "Contract must have a name");

            int id = val["id"].GetInt();
            std::string name = val["name"].GetString();

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

            std::vector<typename Domain::Function *> functions = {};
            if(val.HasMember("functions")) {
                require(val["functions"].IsArray(), "Contract functions must be an array of Function");

                for(rapidjson::Value &fVal : val["functions"].GetArray()) {
                    functions.push_back(readFunction(name, fVal));
                }
            }

            std::vector<Variable<Domain> *> variables = {};
            if(val.HasMember("variables")) {
                require(val["variables"].IsArray(), "Contract variables must be an array of Variable");

                for(rapidjson::Value &vVal : val["variables"].GetArray()) {
                    variables.push_back(readVariable(vVal));
                }
            }

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

            auto &factory = Domain::Factory::instance();
            auto *contract = factory.createContract(module, *model, name, functions, variables);

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

        vanguard::StructType<Domain> *readStruct(rapidjson::Value &val) {
            require(val.HasMember("id") && val["id"].IsNumber(), "Struct must have an id");
            require(val.HasMember("name") && val["name"].IsString(), "Struct must have a name");

            int id = val["id"].GetInt();
            std::string name = val["name"].GetString();

            std::vector<Variable<Domain> *> fields = {};
            if(val.HasMember("fields")) {
                require(val["fields"].IsArray(), "Struct fields must be an array of Variable");

                for(auto &fVal : val["fields"].GetArray()) {
                    fields.push_back(readVariable(fVal));
                }
            }

            auto &factory = Domain::Factory::instance();
            auto *aStruct = factory.createStruct(module, *model, name, fields);

            //auto aStruct = new BlkStruct(llvmTrans, name, fields);
            //storageDecls[id] = aStruct;
            return aStruct;
        }

        /*BlkEnum *readEnum(rapidjson::Value &val);*/
        typename Domain::Function *readFunction(std::string contractName, rapidjson::Value &val) {
            require(val.HasMember("name") && val["name"].IsString(), "Function must have a name");
            require(val.HasMember("isConstructor") && val["isConstructor"].IsBool(), "Must identify if function is a constructor");
            require(val.HasMember("visibility") && val["visibility"].IsString(), "Function must have a visibility");
            require(val.HasMember("mutability") && val["mutability"].IsString(), "Function must have a mutability");

            std::string name = val["name"].GetString();
            bool isConstructor = val["isConstructor"].GetBool();
            Visibility visibility = toVisibility(val["visibility"].GetString());
            Mutability mutability = toMutability(val["mutability"].GetString());

            std::vector<Variable<Domain> *> params = {};
            if(val.HasMember("params")) {
                require(val["params"].IsArray(), "Function params must be array of Variable");

                for(auto &pVal : val["params"].GetArray()) {
                    params.push_back(readVariable(pVal));
                }
            }

            std::vector<Variable<Domain> *> returns = {};
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

            std::string selector = val["selector"].GetString();

            auto &factory = Domain::Factory::instance();
            return factory.createBlkFn(module, *model, contractName, name, selector, isConstructor, visibility, mutability, params, returns, modifiers);
            //BlkFunction<Universe> *fn = new BlkFunction<Universe>(name, selector, isConstructor, visibility, mutability, params, returns, modifiers);
        }
        Variable<Domain> *readVariable(rapidjson::Value &val) {
            require(val.HasMember("type") && val["type"].IsObject(), "Variable must have a type");

            typename Domain::Type *type = readType(val["type"]);

            std::string name = "";
            if(val.HasMember("name")) {
                require(val["name"].IsString(), "Variable name must be a string");
                name = val["name"].GetString();
            }

            auto &factory = Domain::Factory::instance();
            return factory.createVariable(module, *model, name, type);
            //return new BlkVariable(llvmTrans, name, type);
        }

        typename Domain::Type *readType(rapidjson::Value &val) {
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

        ArrayType<Domain> *readArrayType(rapidjson::Value &val) {
            require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
            std::string subType = val["subType"].GetString();
            require(subType == "ArrayType");

            require(val.HasMember("name") && val["name"].IsString(), "ArrayType must have a name");
            require(val.HasMember("base"), "ArrayType must have a base type");
            auto base = readType(val["base"]);
            std::string name = val["name"].GetString();
            auto &factory = Domain::Factory::instance();
            return factory.createArrayType(module, *model, name, base);
            //return new BlkArrayType(llvmTrans, name, base);
        }

        typename Domain::Type *readUserType(rapidjson::Value &val) {
            require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
            std::string subType = val["subType"].GetString();
            require(subType == "UserType");

            require(val.HasMember("name") && val["name"].IsString(), "UserType must have a name");
            require(val.HasMember("refId") && val["refId"].IsNumber(), "UserType must have a reference id");

            std::string name = val["name"].GetString();
            uint id = val["refId"].GetUint();

            auto &factory = Domain::Factory::instance();
            auto userType = factory.createBasicType(module, *model, name);
            //auto userType = new BlkUserType(llvmTrans, name, nullptr);
            //storageRefs[userType] = id;

            return userType;
        }

        MapType<Domain> *readMapType(rapidjson::Value &val) {
            require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
            std::string subType = val["subType"].GetString();
            require(subType == "MapType");

            require(val.HasMember("name") && val["name"].IsString(), "MapType must have a name");
            require(val.HasMember("key"), "MapType must have a key type");
            require(val.HasMember("value"), "MapType must have a value type");
            typename Domain::Type *key = readType(val["key"]);
            typename Domain::Type *value = readType(val["value"]);
            std::string name = val["name"].GetString();
            auto &factory = Domain::Factory::instance();
            return factory.createMapType(module, *model, name, key, value);
            //return new BlkMapType(llvmTrans, name, key, value);
        }

        typename Domain::Type *readElementaryType(rapidjson::Value &val) {
            require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
            std::string subType = val["subType"].GetString();
            require(subType == "ElementaryType");

            require(val.HasMember("name") && val["name"].IsString(), "ElementaryType must have a name");
            std::string name = val["name"].GetString();
            auto &factory = Domain::Factory::instance();
            return factory.createBasicType(module, *model, name);
            //return new BlkType<Type>(name);
            //return new BlkElementaryType(llvmTrans, name);
        }
    };
}



#endif //LIBBLOCKCHAIN_SUMMARYREADER_H
