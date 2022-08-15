#include "Type.h"
#include "LLVMtoVanguard.h"

namespace vanguard{
    
    Type::Type(){}

    //Integer subclass
    IntegerType::IntegerType(const llvm::IntegerType& intT): integer(intT){}

    unsigned IntegerType::getWidth(){
        return integer.getBitWidth()/8;
    }

    std::string IntegerType::getName(){
        return "IntegerT";
    }

    //Array subclass
    ArrayType::ArrayType(const llvm::ArrayType& arr): array(arr){}

    Type* ArrayType::getBaseType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(array.getElementType());
    }

    auto ArrayType::getLength(){
        return array.getNumElements();
    }

    std::string ArrayType::getName(){
        return "array< " + (this->getBaseType())->getName() + " >";
    }

    //Function subclass
    // FunctionT::FunctionT(llvm::FunctionType& func): function(func){}

    // Type* FunctionT::getReturnType(){
    //     LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
    //     return llvmToVanguard->translateType(*function.getReturnType());
    // }

    // unsigned FunctionT::getNumParams(){
    //     return function.getNumParams();
    // }

    // std::list<Type*> FunctionT::getParamsType(){
    //     LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
    //     std::list<Type*> paramsTypeList = {};
    //     for(auto param: function.params()){
    //         paramsTypeList.push_back(llvmToVanguard->translateType(*param));
    //     }
    //     return paramsTypeList;
    // }

    //Pointer subclass
    PointerType::PointerType(const llvm::PointerType& ptr): pointer(ptr){}
    
    bool PointerType::isOpaque(){
        return pointer.isOpaque();
    }

    Type* PointerType::getPointeeType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(pointer.getElementType());
    }

    std::string PointerType::getName(){
        return "pointer< " + (this->getPointeeType())->getName() + " >";
    }

    //Struct subclass
    StructType::StructType(const llvm::StructType& structt): structT(structt){}

    unsigned StructType::getNumFields(){
        return structT.getStructNumElements();
    }

    Type* StructType::getTypeAtIndex(unsigned n){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(structT.getStructElementType(n));
    }

    std::list<Type*> StructType::getFieldTypes(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Type*> fieldTypesList = {};
        int numFields = structT.getStructNumElements();
        for(int n = 0; n < numFields; n++){
            fieldTypesList.push_back(llvmToVanguard.translateType(structT.getStructElementType(n)));
        }
        return fieldTypesList;
    }

    std::string StructType::getName(){
        return std::string(structT.getName());
    }

    //Vector subclass
    VectorType::VectorType(const llvm::VectorType& vec): vector(vec){}

    Type* VectorType::getBaseType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(vector.getElementType());
    }

    std::string VectorType::getName(){
        return "vector< " + (this->getBaseType())->getName() + " >";
    }

}