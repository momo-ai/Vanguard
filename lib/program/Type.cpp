#include "Type.h"
#include "LLVMFactory.h"

namespace vanguard{
    
    Type::Type(UnitFactory &factory, TypeSquared typeType) : typeType(typeType), factory{factory} {}

    void IntegerType::accept(TypeVisitor &v) const {
        v.visit(*this);
    }

    void ObjectType::accept(TypeVisitor &v) const {
        v.visit(*this);
    }

    void MapType::accept(TypeVisitor &v) const {
        v.visit(*this);
    }

    void ArrayType::accept(TypeVisitor &v) const {
        v.visit(*this);
    }

    void PointerType::accept(TypeVisitor &v) const {
        v.visit(*this);
    }

    void StructType::accept(TypeVisitor &v) const {
        v.visit(*this);
    }

    void VoidType::accept(TypeVisitor &v) const {
        v.visit(*this);
    }

    void LocationType::accept(TypeVisitor &v) const {
        v.visit(*this);
    }

    void UnknownType::accept(TypeVisitor &v) const {
        v.visit(*this);
    }
/*
    //Integer subclass
    IntegerType::IntegerType(UnitFactory &factory, const llvm::IntegerType& intT): Type(factory), integer(intT){}

    unsigned IntegerType::width(){
        return integer.getBitWidth()/8;
    }

    std::string IntegerType::name() const {
        return "IntegerType";
    }

    const llvm::IntegerType &IntegerType::unwrap(){
        return integer;
    }

    //Array subclass
    ArrayType::ArrayType(UnitFactory &factory, const llvm::ArrayType& arr): Type(factory), array(arr){}

    Type* ArrayType::baseType() const {
        return factory.createType(array.getElementType());
    }

    uint64_t ArrayType::length() const {
        return array.getNumElements();
    }

    std::string ArrayType::name() const {
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
    PointerType::PointerType(UnitFactory &factory, const llvm::PointerType& ptr): Type(factory), pointer(ptr){}
    
    bool PointerType::isOpaque(){
        return pointer.isOpaque();
    }

    Type* PointerType::referencedType() const {
        return factory.createType(pointer.getElementType());
    }

    std::string PointerType::name() const {
        return "PointerType< " + (this->referencedType())->name() + " >";
    }

    const llvm::PointerType &PointerType::unwrap(){
        return pointer;
    }

    //Struct subclass
    StructType::StructType(UnitFactory &factory, const llvm::StructType& structt): Type(factory), structT(structt){}

    unsigned StructType::numFields(){
        return structT.getStructNumElements();
    }

    Type* StructType::getTypeAtIndex(unsigned n){
        return factory.createType(structT.getStructElementType(n));
    }

    std::list<Type*> StructType::fieldTypes(){
        std::list<Type*> fieldTypesList = {};
        unsigned numFields = structT.getStructNumElements();
        for(unsigned n = 0; n < numFields; n++){
            fieldTypesList.push_back(factory.createType(structT.getStructElementType(n)));
        }
        return fieldTypesList;
    }

    std::string StructType::name() const {
        return std::string(structT.getName());
    }

    const llvm::StructType &StructType::unwrap(){
        return structT;
    }

    //Vector subclass
    VectorType::VectorType(UnitFactory &factory, const llvm::VectorType& vec): Type(factory), vector(vec){}

    Type* VectorType::baseType() const {
        return factory.createType(vector.getElementType());
    }

    std::string VectorType::name() const {
        return "VectorType< " + (this->baseType())->name() + " >";
    }

    const llvm::VectorType &VectorType::unwrap(){
        return vector;
    }

    //Void Subclass
    VoidType::VoidType(UnitFactory &factory, const llvm::Type &vt): Type(factory), voidType(vt) {}

    std::string VoidType::name() const {
        return "VoidType";
    }

    const llvm::Type &VoidType::unwrap() {
        return voidType;
    }

    //Label Subclass
    LabelType::LabelType(UnitFactory &factory, const llvm::Type &lbt): Type(factory), labelType(lbt) {}

    std::string LabelType::name() const {
        return "LabelType";
    }

    const llvm::Type &LabelType::unwrap() {
        return labelType;
    }*/
}