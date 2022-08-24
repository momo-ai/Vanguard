#include "Value.h"
#include "LLVMtoVanguard.h"

namespace vanguard{
    Value::Value(ValueClassEnum vc): valueClass(vc){}

    ValueClassEnum Value::getClass() const{
        return valueClass;
    }

    GlobalVariable::GlobalVariable(const llvm::GlobalVariable &gv): Value(GLOBAL_VARIABLE), globalVariable(gv) {}

    Type* GlobalVariable::getType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(globalVariable.getType());
    }

    bool GlobalVariable::hasName(){
        return globalVariable.hasName();
    }

    std::string GlobalVariable::getName(){
        return std::string(globalVariable.getName());
    }

    const llvm::GlobalVariable &GlobalVariable::unwrap(){
        return globalVariable;
    }

    void GlobalVariable::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //Argument
    Argument::Argument(const llvm::Argument& arg): Value(ARGUMENT), argument(arg){}

    Type* Argument::getType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(argument.getType());
    }

    bool Argument::hasName(){
        return argument.hasName();
    }

    std::string Argument::getName(){
        return std::string(argument.getName());
    }

    const llvm::Argument &Argument::unwrap(){
        return argument;
    }

    void Argument::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //InstructionVariable
    InstructionVariable::InstructionVariable(const llvm::Instruction& instv): Value(INSTRUCTION_VARIABLE), instructionVariable(instv){}

    Type* InstructionVariable::getType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(instructionVariable.getType());
    }

    bool InstructionVariable::hasName(){
        return instructionVariable.hasName();
    }

    std::string InstructionVariable::getName(){
        return std::string(instructionVariable.getName());
    }

    const llvm::Instruction &InstructionVariable::unwrap(){
        return instructionVariable;
    }

    void InstructionVariable::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //Integer
    IntegerLiteral::IntegerLiteral(const llvm::ConstantInt& ci): Value(INTEGER_LITERAL), constInt(ci){}

    Type* IntegerLiteral::getType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(constInt.getType());
    }

    int IntegerLiteral::getValue(){
        return (int)constInt.getValue().getLimitedValue();
    }

    const llvm::ConstantInt &IntegerLiteral::unwrap(){
        return constInt;
    }

    void IntegerLiteral::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //String
    StringLiteral::StringLiteral(const llvm::ConstantDataSequential & cs): Value(STRING_LITERAL), constSeq(cs){}

    Type* StringLiteral::getType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(constSeq.getType());
    }

    std::string StringLiteral::getValue(){
        return constSeq.getAsString().str();
    }

    const llvm::ConstantDataSequential &StringLiteral::unwrap(){
        return constSeq;
    }

    void StringLiteral::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //Boolean
    BooleanLiteral::BooleanLiteral(bool b): constBool(b){}

    bool BooleanLiteral::getValue(){
        return constBool;
    }

    //Memory Address
    MemoryAddress::MemoryAddress(const llvm::Value* ptr, const llvm::Value* idx, unsigned long sz): Value(MEMORY_ADDRESS), pointer(ptr) , index(idx), size(sz){}

    MemoryAddress::MemoryAddress(const llvm::Value* ptr, unsigned long sz): Value(MEMORY_ADDRESS), pointer(ptr), size(sz){}

    Type* MemoryAddress::getType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(pointer->getType());
    }

    const llvm::Value* MemoryAddress::getPointer(){
        return pointer;
    }

    const llvm::Value* MemoryAddress::getIndex(){
        return index;
    }

    unsigned long MemoryAddress::getSize(){
        return size;
    }

    void MemoryAddress::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

    //Constant
    Constant::Constant(const llvm::Constant &cst): Value(CONSTANT), constant(cst) {}

    Type* Constant::getType(){
        auto &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(constant.getType());
    }

    void Constant::accept(ValueClassVisitor &v) const {
        return v.visit(*this);
    }

}