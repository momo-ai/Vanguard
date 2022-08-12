#include "Type.h"
#include "LLVMtoVanguard.h"

namespace vanguard{
    
    Type::Type(){}

    //Integer subclass
    IntegerT::IntegerT(llvm::IntegerType& intT): integer(intT){}

    unsigned IntegerT::getWidth(){
        return integer.getBitWidth()/8;
    }

    std::string IntegerT::getName(){
        return "IntegerT";
    }

    llvm::IntegerType* IntegerT::unwrap(){
        return &integer;
    }

    //Array subclass
    ArrayT::ArrayT(llvm::ArrayType& arr): array(arr){}

    Type* ArrayT::getBaseType(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateType(*array.getElementType());
    }

    auto ArrayT::getLength(){
        return array.getNumElements();
    }

    std::string ArrayT::getName(){
        return "array< " + (this->getBaseType())->getName() + " >";
    }

    llvm::ArrayType* ArrayT::unwrap(){
        return &array;
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
    PointerT::PointerT(llvm::PointerType& ptr): pointer(ptr){}
    
    bool PointerT::isOpaque(){
        return pointer.isOpaque();
    }

    Type* PointerT::getPointeeType(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateType(*pointer.getElementType());
    }

    std::string PointerT::getName(){
        return "pointer< " + (this->getPointeeType())->getName() + " >";
    }

    llvm::PointerType* PointerT::unwrap(){
        return &pointer;
    }

    //Struct subclass
    StructT::StructT(llvm::StructType& structt): structT(structt){}

    unsigned StructT::getNumFields(){
        return structT.getStructNumElements();
    }

    Type* StructT::getTypeAtIndex(unsigned n){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateType(*structT.getStructElementType(n));
    }

    std::list<Type*> StructT::getFieldTypes(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Type*> fieldTypesList = {};
        int numFields = structT.getStructNumElements();
        for(int n = 0; n < numFields; n++){
            fieldTypesList.push_back(llvmToVanguard->translateType(*structT.getStructElementType(n)));
        }
        return fieldTypesList;
    }

    std::string StructT::getName(){
        return std::string(structT.getName());
    }

    llvm::StructType* StructT::unwrap(){
        return &structT;
    }

    //Vector subclass
    VectorT::VectorT(llvm::VectorType& vec): vector(vec){}

    Type* VectorT::getBaseType(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateType(*vector.getElementType());
    }

    std::string VectorT::getName(){
        return "vector< " + (this->getBaseType())->getName() + " >";
    }

    llvm::VectorType* VectorT::unwrap(){
        return &vector;
    }

}