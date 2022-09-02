#include "Value.h"
#include "LLVMFactory.h"

namespace vanguard{
    Value::Value(UnitFactory &factory, ValueClassEnum vc): factory(factory), valClass(vc){}

    ValueClassEnum Value::valueClass() const{
        return valClass;
    }

    GlobalVariable::GlobalVariable(UnitFactory &factory, const llvm::GlobalVariable &gv): Variable(factory, GLOBAL_VARIABLE), globalVariable(gv) {}

    Type* GlobalVariable::type() const{
        return factory.createType(globalVariable.getType());
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
    Argument::Argument(UnitFactory &factory, const llvm::Argument& arg): Variable(factory, ARGUMENT), argument(arg){}

    Type* Argument::type() const{
        return factory.createType(argument.getType());
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
    InstructionVariable::InstructionVariable(UnitFactory &factory, const llvm::Instruction& instv): Variable(factory, INSTRUCTION_VARIABLE), instructionVariable(instv){}

    Type* InstructionVariable::type() const{
        return factory.createType(instructionVariable.getType());
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
    IntegerLiteral::IntegerLiteral(UnitFactory &factory, const llvm::ConstantInt& ci): Literal(factory, INTEGER_LITERAL), constInt(ci){}

    Type* IntegerLiteral::type() const{
        return factory.createType(constInt.getType());
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
    StringLiteral::StringLiteral(UnitFactory &factory, const llvm::ConstantDataSequential & cs): Literal(factory, STRING_LITERAL), constSeq(cs){}

    Type* StringLiteral::type() const{
        return factory.createType(constSeq.getType());
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
    BooleanLiteral::BooleanLiteral(UnitFactory &factory, bool b): Literal(factory, BOOLEAN_LITERAL), constBool(b){}

    bool BooleanLiteral::value() const{
        return constBool;
    }

    Pointer::Pointer(UnitFactory &factory, const llvm::Value *base, const llvm::Value *offset, const llvm::Type *type) : Value(factory, POINTER), ptrType(type), ptrBase(base), ptrOffset(offset) {}

    Value *Pointer::base() const {
        return factory.createVal(ptrBase);
    }

    Value *Pointer::offset() const {
        return factory.createVal(ptrOffset);
    }

    Type *Pointer::refType() const {
        return factory.createType(ptrType);
    }

    Type* Pointer::type() const {
        return factory.createType(ptrBase->getType());
    }

    //Memory Address
    MemoryRegion::MemoryRegion(UnitFactory &factory, const Pointer *ptr, unsigned long sz): Value(factory, MEMORY_REGION), ptr(ptr) , memSize(sz){}


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
    Constant::Constant(UnitFactory &factory, const llvm::Constant &cst): Value(factory, CONSTANT), constant(cst) {}

    Type* Constant::type() const{
        return factory.createType(constant.getType());
    }

    unsigned Constant::getLLVMValueID() const {
        return constant.getValueID();
    }

    void Constant::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    Location::Location(UnitFactory &factory, const llvm::BasicBlock &blk): Value(factory, LOCATION), location(blk) {}

    Type *Location::type() const {
        return factory.createType(location.getType());
    }

    void Location::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    Universe::Block &Location::loc() const {
        return *factory.createBlk(&location);
    }
}