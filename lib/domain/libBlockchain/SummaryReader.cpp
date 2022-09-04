//
// Created by Jon Stephens on 3/23/22.
//

#include "SummaryReader.h"
#include "Blockchain.h"
#include "BlockchainFactory.h"
#include "BlkType.h"
#include "solidity/SolangModel.h"
//#include "domain/libBlockchain/include/solidity/Solidity.h"
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <stdexcept>
#include <iostream>
//#include "domain/libBlockchain/include/solidity/SolangModel.h"
//#include "domain/libBlockchain/include/ink/InkModel.h"
//#include "domain/libBlockchain/include/ink/Ink.h"
//#include "../include/BlkEvent.h"

using namespace std;

namespace vanguard {

    SummaryReader::SummaryReader(const llvm::Module &mod, const std::string& projectFile, BlockchainFactory *factory) : module(mod), factory(factory) {
        model = nullptr;
        ifstream inStream(projectFile);
        rapidjson::IStreamWrapper jsonStream(inStream);
        cout << "starting" << endl;

        rapidjson::Document doc;
        doc.ParseStream(jsonStream);
        readSummary(doc);
    }

    std::vector<Blockchain<Universe>::Contract *> SummaryReader::contracts() const {
        return foundContracts;
    }

    /*Blockchain *SummaryReader::blockchain() {
        return summary;
    }*/

    void error(string msg) {
        throw std::runtime_error(msg);
    }

    void require(bool cond, string msg = "") {
        if(!cond) {
            error(msg);
        }
    }

    void SummaryReader::readSummary(rapidjson::Value &val) {
        require(val.HasMember("compiler") && val["compiler"].IsString(), "Summary must declare compiler");
        require(val.HasMember("version") && val["version"].IsString(), "Summary must declare version");

        string compiler = val["compiler"].GetString();
        string version = val["version"].GetString();

        //Blockchain *blockchain;
        //vector<Blockchain<Universe>::Contract *> contracts = {};

        if(compiler == "Solang") {
            model = new SolangModel();
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

    Blockchain<Universe>::Contract *SummaryReader::readContract(rapidjson::Value &val) {
        require(val.HasMember("id") && val["id"].IsNumber(), "Contract must have an id");
        require(val.HasMember("name") && val["name"].IsString(), "Contract must have a name");

        int id = val["id"].GetInt();
        string name = val["name"].GetString();

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

        vector<BlkFunction<Blockchain<Universe>> *> functions = {};
        if(val.HasMember("functions")) {
            require(val["functions"].IsArray(), "Contract functions must be an array of Function");

            for(rapidjson::Value &fVal : val["functions"].GetArray()) {
                functions.push_back(readFunction(name, fVal));
            }
        }

        vector<Variable *> variables = {};
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

        auto *contract = factory->createContract(module, *model, name, functions, variables);
        //auto *contract = new Blockchain<Universe>::Contract(name, functions, variables);
        //storageDecls[id] = contract;
        return contract;
    }

    /*BlkEvent *SummaryReader::readEvent(rapidjson::Value &val) {
        require(val.HasMember("name") && val["name"].IsString(), "Function must have a name");

        string name = val["name"].GetString();

        vector<BlkVariable *> params = {};
        if(val.HasMember("params")) {
            require(val["params"].IsArray(), "Function params must be array of Variable");

            for(auto &pVal : val["params"].GetArray()) {
                params.push_back(readVariable(pVal));
            }
        }

        BlkEvent *event = new BlkEvent(llvmTrans, name, params);

        return event;
    }*/

    BlkStructType<StructType> *SummaryReader::readStruct(rapidjson::Value &val) {
        require(val.HasMember("id") && val["id"].IsNumber(), "Struct must have an id");
        require(val.HasMember("name") && val["name"].IsString(), "Struct must have a name");

        int id = val["id"].GetInt();
        string name = val["name"].GetString();

        vector<Variable *> fields = {};
        if(val.HasMember("fields")) {
            require(val["fields"].IsArray(), "Struct fields must be an array of Variable");

            for(auto &fVal : val["fields"].GetArray()) {
                fields.push_back(readVariable(fVal));
            }
        }

        auto *aStruct = factory->createStruct(module, *model, name, fields);

        //auto aStruct = new BlkStruct(llvmTrans, name, fields);
        //storageDecls[id] = aStruct;
        return aStruct;
    }

    /*BlkEnum *SummaryReader::readEnum(rapidjson::Value &val) {
        require(val.HasMember("id") && val["id"].IsNumber(), "Struct must have an id");
        require(val.HasMember("name") && val["name"].IsString(), "Struct must have a name");

        int id = val["id"].GetInt();
        string name = val["name"].GetString();

        map<string, int> values = {};
        if(val.HasMember("values")) {
            require(val["values"].IsObject(), "Enum values must be an object");
            for(auto &enumVal : val["values"].GetObject()) {
                require(enumVal.name.IsString(), "Enum value names must be a string");
                require(enumVal.value.IsNumber(), "Enum value must map to number");
                string valName = enumVal.name.GetString();
                int valId = enumVal.value.GetInt();
                values[valName] = valId;
            }
        }

        auto anEnum = new BlkEnum(llvmTrans, name, values);
        storageDecls[id] = anEnum;
        return anEnum;
    }*/

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

    BlkFunction<Blockchain<Universe>> *SummaryReader::readFunction(std::string contractName, rapidjson::Value &val) {
        require(val.HasMember("name") && val["name"].IsString(), "Function must have a name");
        require(val.HasMember("isConstructor") && val["isConstructor"].IsBool(), "Must identify if function is a constructor");
        require(val.HasMember("visibility") && val["visibility"].IsString(), "Function must have a visibility");
        require(val.HasMember("mutability") && val["mutability"].IsString(), "Function must have a mutability");

        string name = val["name"].GetString();
        bool isConstructor = val["isConstructor"].GetBool();
        Visibility visibility = toVisibility(val["visibility"].GetString());
        Mutability mutability = toMutability(val["mutability"].GetString());

        vector<Variable *> params = {};
        if(val.HasMember("params")) {
            require(val["params"].IsArray(), "Function params must be array of Variable");

            for(auto &pVal : val["params"].GetArray()) {
                params.push_back(readVariable(pVal));
            }
        }

        vector<Variable *> returns = {};
        if(val.HasMember("returns")) {
            require(val["returns"].IsArray(), "Function returns must be array of Variable");

            for(auto &rVal : val["returns"].GetArray()) {
                returns.push_back(readVariable(rVal));
            }
        }

        vector<string> modifiers = {};
        if(val.HasMember("modifiers")) {
            require(val["modifiers"].IsArray(), "Function modifiers must be array of string");

            for(auto &mVal : val["modifiers"].GetArray()) {
                require(mVal.IsString(), "Found modifier that isn't a string modifier");

                modifiers.emplace_back(mVal.GetString());
            }
        }

        std::string selector = val["selector"].GetString();

        return factory->createBlkFunction(module, *model, contractName, name, selector, isConstructor, visibility, mutability, params, returns, modifiers);
        //BlkFunction<Universe> *fn = new BlkFunction<Universe>(name, selector, isConstructor, visibility, mutability, params, returns, modifiers);
    }

    BlkVariable<Variable> *SummaryReader::readVariable(rapidjson::Value &val) {
        require(val.HasMember("type") && val["type"].IsObject(), "Variable must have a type");

        Type *type = readType(val["type"]);

        string name = "";
        if(val.HasMember("name")) {
            require(val["name"].IsString(), "Variable name must be a string");
            name = val["name"].GetString();
        }

        return factory->createVariable(module, *model, name, type);
        //return new BlkVariable(llvmTrans, name, type);
    }

    Type *SummaryReader::readType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        string subType = val["subType"].GetString();

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

        error(string("Unknown Type: ") + subType);
        return nullptr;
    }

    ArrayType *SummaryReader::readArrayType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        string subType = val["subType"].GetString();
        require(subType == "ArrayType");

        require(val.HasMember("name") && val["name"].IsString(), "ArrayType must have a name");
        require(val.HasMember("base"), "ArrayType must have a base type");
        auto base = readType(val["base"]);
        string name = val["name"].GetString();
        return factory->createArrayType(module, *model, name, base);
        //return new BlkArrayType(llvmTrans, name, base);
    }

    Type *SummaryReader::readUserType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        string subType = val["subType"].GetString();
        require(subType == "UserType");

        require(val.HasMember("name") && val["name"].IsString(), "UserType must have a name");
        require(val.HasMember("refId") && val["refId"].IsNumber(), "UserType must have a reference id");

        string name = val["name"].GetString();
        uint id = val["refId"].GetUint();

        auto userType = factory->createBasicType(module, *model, name);
        //auto userType = new BlkUserType(llvmTrans, name, nullptr);
        //storageRefs[userType] = id;

        return userType;
    }

    MapType *SummaryReader::readMapType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        string subType = val["subType"].GetString();
        require(subType == "MapType");

        require(val.HasMember("name") && val["name"].IsString(), "MapType must have a name");
        require(val.HasMember("key"), "MapType must have a key type");
        require(val.HasMember("value"), "MapType must have a value type");
        Type *key = readType(val["key"]);
        Type *value = readType(val["value"]);
        string name = val["name"].GetString();
        return factory->createMapType(module, *model, name, key, value);
        //return new BlkMapType(llvmTrans, name, key, value);
    }

    Type *SummaryReader::readElementaryType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        string subType = val["subType"].GetString();
        require(subType == "ElementaryType");

        require(val.HasMember("name") && val["name"].IsString(), "ElementaryType must have a name");
        string name = val["name"].GetString();
        return factory->createBasicType(module, *model, name);
        //return new BlkType<Type>(name);
        //return new BlkElementaryType(llvmTrans, name);
    }
}