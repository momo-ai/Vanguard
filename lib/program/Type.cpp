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
        return "IntegerType";
    }

    const llvm::IntegerType &IntegerType::unwrap(){
        return integer;
    }

    //Array subclass
    ArrayType::ArrayType(const llvm::ArrayType& arr): array(arr){}

    Type* ArrayType::getBaseType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(array.getElementType());
    }

    uint64_t ArrayType::getLength(){
        return array.getNumElements();
    }

    std::string ArrayType::getName(){
        return "ArrayType< " + (this->getBaseType())->getName() + " >";
    }

    const llvm::ArrayType &ArrayType::unwrap(){
        return array;
    }

    //Function subclass
//     FunctionT::FunctionT(const llvm::FunctionType& func): function(func){}
//
//     Type* FunctionT::getReturnType(){
//         LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
//         return llvmToVanguard.translateType(function.getReturnType());
//     }
//
//     unsigned FunctionT::getNumParams(){
//         return function.getNumParams();
//     }
//
//     std::list<Type*> FunctionT::getParamsType(){
//         LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
//         std::list<Type*> paramsTypeList = {};
//         for(auto param: function.params()){
//             paramsTypeList.push_back(llvmToVanguard.translateType(param));
//         }
//         return paramsTypeList;
//     }
//
//     std::string FunctionT::getName() {
//        return "Function";
//    }

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
        return "PointerType< " + (this->getPointeeType())->getName() + " >";
    }

    const llvm::PointerType &PointerType::unwrap(){
        return pointer;
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
        unsigned numFields = structT.getStructNumElements();
        for(unsigned n = 0; n < numFields; n++){
            fieldTypesList.push_back(llvmToVanguard.translateType(structT.getStructElementType(n)));
        }
        return fieldTypesList;
    }

    std::string StructType::getName(){
        return std::string(structT.getName());
    }

    const llvm::StructType &StructType::unwrap(){
        return structT;
    }

    //Vector subclass
    VectorType::VectorType(const llvm::VectorType& vec): vector(vec){}

    Type* VectorType::getBaseType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(vector.getElementType());
    }

    std::string VectorType::getName(){
        return "VectorType< " + (this->getBaseType())->getName() + " >";
    }

    const llvm::VectorType &VectorType::unwrap(){
        return vector;
    }

    VoidType::VoidType(const llvm::Type &vt): voidType(vt) {}

    std::string VoidType::getName() {
        return "VoidType";
    }

    const llvm::Type &VoidType::unwrap() {
        return voidType;
    }
}