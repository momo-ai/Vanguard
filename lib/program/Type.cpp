#include "Type.h"
#include "LLVMtoVanguard.h"

namespace vanguard{
    
    Type::Type(){}

    //Integer subclass
    IntegerType::IntegerType(const llvm::IntegerType& intT): integer(intT){}

    unsigned IntegerType::width(){
        return integer.getBitWidth()/8;
    }

    std::string IntegerType::name(){
        return "IntegerType";
    }

    const llvm::IntegerType &IntegerType::unwrap(){
        return integer;
    }

    //Array subclass
    ArrayType::ArrayType(const llvm::ArrayType& arr): array(arr){}

    Type* ArrayType::baseType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(array.getElementType());
    }

    uint64_t ArrayType::length(){
        return array.getNumElements();
    }

    std::string ArrayType::name(){
        return "ArrayType< " + (this->baseType())->name() + " >";
    }

    const llvm::ArrayType &ArrayType::unwrap(){
        return array;
    }

    //Function subclass
//     FunctionT::FunctionT(const llvm::FunctionType& func): function(func){}
//
//     Type* FunctionT::returnType(){
//         LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
//         return llvmToVanguard.translateType(function.returnType());
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
//     std::string FunctionT::name() {
//        return "Function";
//    }

    //Pointer subclass
    PointerType::PointerType(const llvm::PointerType& ptr): pointer(ptr){}
    
    bool PointerType::isOpaque(){
        return pointer.isOpaque();
    }

    Type* PointerType::referencedType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(pointer.getElementType());
    }

    std::string PointerType::name(){
        return "PointerType< " + (this->referencedType())->name() + " >";
    }

    const llvm::PointerType &PointerType::unwrap(){
        return pointer;
    }

    //Struct subclass
    StructType::StructType(const llvm::StructType& structt): structT(structt){}

    unsigned StructType::numFields(){
        return structT.getStructNumElements();
    }

    Type* StructType::getTypeAtIndex(unsigned n){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(structT.getStructElementType(n));
    }

    std::list<Type*> StructType::fieldTypes(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Type*> fieldTypesList = {};
        unsigned numFields = structT.getStructNumElements();
        for(unsigned n = 0; n < numFields; n++){
            fieldTypesList.push_back(llvmToVanguard.translateType(structT.getStructElementType(n)));
        }
        return fieldTypesList;
    }

    std::string StructType::name(){
        return std::string(structT.getName());
    }

    const llvm::StructType &StructType::unwrap(){
        return structT;
    }

    //Vector subclass
    VectorType::VectorType(const llvm::VectorType& vec): vector(vec){}

    Type* VectorType::baseType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(vector.getElementType());
    }

    std::string VectorType::name(){
        return "VectorType< " + (this->baseType())->name() + " >";
    }

    const llvm::VectorType &VectorType::unwrap(){
        return vector;
    }

    //Void Subclass
    VoidType::VoidType(const llvm::Type &vt): voidType(vt) {}

    std::string VoidType::name() {
        return "VoidType";
    }

    const llvm::Type &VoidType::unwrap() {
        return voidType;
    }

    //Label Subclass
    LabelType::LabelType(const llvm::Type &lbt): labelType(lbt) {}

    std::string LabelType::name() {
        return "LabelType";
    }

    const llvm::Type &LabelType::unwrap() {
        return labelType;
    }
}