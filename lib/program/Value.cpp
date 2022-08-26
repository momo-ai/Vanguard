#include "Value.h"
#include "LLVMtoVanguard.h"

namespace vanguard{
    Value::Value(ValueClassEnum vc): valueClass(vc){}

    ValueClassEnum Value::getClass() const{
        return valueClass;
    }

    GlobalVariable::GlobalVariable(const llvm::GlobalVariable &gv): Value(GLOBAL_VARIABLE), globalVariable(gv) {}

    Type* GlobalVariable::getType() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(globalVariable.getType());
    }

    bool GlobalVariable::hasName() const{
        return globalVariable.hasName();
    }

    std::string GlobalVariable::getName() const{
        return std::string(globalVariable.getName());
    }

    const llvm::GlobalVariable &GlobalVariable::unwrap() const{
        return globalVariable;
    }

    void GlobalVariable::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //Argument
    Argument::Argument(const llvm::Argument& arg): Value(ARGUMENT), argument(arg){}

    Type* Argument::getType() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(argument.getType());
    }

    bool Argument::hasName() const{
        return argument.hasName();
    }

    std::string Argument::getName() const{
        return std::string(argument.getName());
    }

    const llvm::Argument &Argument::unwrap() const{
        return argument;
    }

    void Argument::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //InstructionVariable
    InstructionVariable::InstructionVariable(const llvm::Instruction& instv): Value(INSTRUCTION_VARIABLE), instructionVariable(instv){}

    Type* InstructionVariable::getType() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(instructionVariable.getType());
    }

    bool InstructionVariable::hasName() const{
        return instructionVariable.hasName();
    }

    std::string InstructionVariable::getName() const{
        return std::string(instructionVariable.getName());
    }

    const llvm::Instruction &InstructionVariable::unwrap() const{
        return instructionVariable;
    }

    void InstructionVariable::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //Integer
    IntegerLiteral::IntegerLiteral(const llvm::ConstantInt& ci): Value(INTEGER_LITERAL), constInt(ci){}

    Type* IntegerLiteral::getType() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(constInt.getType());
    }

    int IntegerLiteral::getValue() const{
        return (int)constInt.getValue().getLimitedValue();
    }

    const llvm::ConstantInt &IntegerLiteral::unwrap() const{
        return constInt;
    }

    void IntegerLiteral::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //String
    StringLiteral::StringLiteral(const llvm::ConstantDataSequential & cs): Value(STRING_LITERAL), constSeq(cs){}

    Type* StringLiteral::getType() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(constSeq.getType());
    }

    std::string StringLiteral::getValue() const{
        return constSeq.getAsString().str();
    }

    const llvm::ConstantDataSequential &StringLiteral::unwrap() const{
        return constSeq;
    }

    void StringLiteral::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //Boolean
    BooleanLiteral::BooleanLiteral(bool b): constBool(b){}

    bool BooleanLiteral::getValue() const{
        return constBool;
    }

    //Memory Address
    MemoryAddress::MemoryAddress(const llvm::Value* ptr, const llvm::Value* idx, unsigned long sz): Value(MEMORY_ADDRESS), pointer(ptr) , index(idx), size(sz){}

    MemoryAddress::MemoryAddress(const llvm::Value* ptr, unsigned long sz): Value(MEMORY_ADDRESS), pointer(ptr), size(sz){}

    Type* MemoryAddress::getType() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(pointer->getType());
    }

    Value *MemoryAddress::getPointer() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(pointer);
    }

    Value *MemoryAddress::getIndex() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(index);
    }

    const llvm::Value* MemoryAddress::getLLVMPointer() const{
        return pointer;
    }

    const llvm::Value* MemoryAddress::getLLVMIndex() const{
        return index;
    }

    unsigned long MemoryAddress::getSize() const{
        return size;
    }

    void MemoryAddress::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //Constant
    Constant::Constant(const llvm::Constant &cst): Value(CONSTANT), constant(cst) {}

    Type* Constant::getType() const{
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(constant.getType());
    }

    unsigned Constant::getLLVMValueID() const {
        return constant.getValueID();
    }

    void Constant::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    BlockValue::BlockValue(const llvm::BasicBlock &blk): Value(BLOCK), block(blk) {}

    Type *BlockValue::getType() const {
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(block.getType());
    }

    unsigned BlockValue::getLLVMValueID() const {
        return block.getValueID();
    }

    void BlockValue::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

}