#include "Value.h"
#include "LLVMtoVanguard.h"

namespace vanguard{
    Value::Value(ValueClassEnum vc): valClass(vc){}

    ValueClassEnum Value::valueClass() const{
        return valClass;
    }

    GlobalVariable::GlobalVariable(const llvm::GlobalVariable &gv): Variable(GLOBAL_VARIABLE), globalVariable(gv) {}

    Type* GlobalVariable::type() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(globalVariable.getType());
    }

    bool GlobalVariable::hasName() const{
        return globalVariable.hasName();
    }

    std::string GlobalVariable::name() const{
        return std::string(globalVariable.getName());
    }

    const llvm::GlobalVariable &GlobalVariable::unwrap() const{
        return globalVariable;
    }

    void GlobalVariable::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //Argument
    Argument::Argument(const llvm::Argument& arg): Variable(ARGUMENT), argument(arg){}

    Type* Argument::type() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(argument.getType());
    }

    bool Argument::hasName() const{
        return argument.hasName();
    }

    std::string Argument::name() const{
        return std::string(argument.getName());
    }

    const llvm::Argument &Argument::unwrap() const{
        return argument;
    }

    void Argument::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //InstructionVariable
    InstructionVariable::InstructionVariable(const llvm::Instruction& instv): Variable(INSTRUCTION_VARIABLE), instructionVariable(instv){}

    Type* InstructionVariable::type() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(instructionVariable.getType());
    }

    bool InstructionVariable::hasName() const{
        return instructionVariable.hasName();
    }

    std::string InstructionVariable::name() const{
        return std::string(instructionVariable.getName());
    }

    const llvm::Instruction &InstructionVariable::unwrap() const{
        return instructionVariable;
    }

    void InstructionVariable::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //Integer
    IntegerLiteral::IntegerLiteral(const llvm::ConstantInt& ci): Literal(INTEGER_LITERAL), constInt(ci){}

    Type* IntegerLiteral::type() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(constInt.getType());
    }

    int IntegerLiteral::value() const{
        return (int)constInt.getValue().getLimitedValue();
    }

    const llvm::ConstantInt &IntegerLiteral::unwrap() const{
        return constInt;
    }

    void IntegerLiteral::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //String
    StringLiteral::StringLiteral(const llvm::ConstantDataSequential & cs): Literal(STRING_LITERAL), constSeq(cs){}

    Type* StringLiteral::type() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(constSeq.getType());
    }

    std::string StringLiteral::value() const{
        return constSeq.getAsString().str();
    }

    const llvm::ConstantDataSequential &StringLiteral::unwrap() const{
        return constSeq;
    }

    void StringLiteral::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //Boolean
    BooleanLiteral::BooleanLiteral(bool b): Literal(BOOLEAN_LITERAL), constBool(b){}

    bool BooleanLiteral::value() const{
        return constBool;
    }

    Pointer::Pointer(const llvm::Value *base, const llvm::Value *offset, const llvm::Type *type) : Value(POINTER), ptrType(type), ptrBase(base), ptrOffset(offset) {}

    Value *Pointer::base() const {
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ptrBase);
    }

    Value *Pointer::offset() const {
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ptrOffset);
    }

    Type *Pointer::refType() const {
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(ptrType);
    }

    Type* Pointer::type() const {
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(ptrBase->getType());
    }

    //Memory Address
    MemoryRegion::MemoryRegion(const Pointer *ptr, unsigned long sz): Value(MEMORY_REGION), ptr(ptr) , memSize(sz){}


    /*Type* MemoryRegion::getType() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(pointer->type());
    }*/

    /*Value *MemoryRegion::pointer() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(pointer);
    }

    Value *MemoryRegion::getIndex() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(index);
    }

    const llvm::Value* MemoryRegion::getLLVMPointer() const{
        return pointer;
    }

    const llvm::Value* MemoryRegion::getLLVMIndex() const{
        return index;
    }*/

    const Pointer *MemoryRegion::pointer() const {
        return ptr;
    }

    unsigned long MemoryRegion::size() const{
        return memSize;
    }

    Type* MemoryRegion::type() const {
        return ptr->refType();
    }

    void MemoryRegion::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    void Pointer::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //Constant
    Constant::Constant(const llvm::Constant &cst): Value(CONSTANT), constant(cst) {}

    Type* Constant::type() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(constant.getType());
    }

    unsigned Constant::getLLVMValueID() const {
        return constant.getValueID();
    }

    void Constant::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    Location::Location(const llvm::BasicBlock &blk): Value(LOCATION), location(blk) {}

    Type *Location::type() const {
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(location.getType());
    }

    void Location::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    vanguard::Block &Location::loc() const {
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return *llvmToVanguard.translateBlock(&location);
    }
}