#include "Value.h"
#include "LLVMtoVanguard.h"

namespace vanguard{
    Value::Value(const ValueClass vc): valueClass(vc){}

    ValueClass Value::getClass() const{
        return valueClass;
    }

    Variable::Variable(const ValueClass vc): Value(vc), valueClass(vc){}

    GlobalVariable::GlobalVariable(const llvm::GlobalVariable &gv): Variable(GLOBAL_VARIABLE), globalVariable(gv) {}

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

    //Argument
    Argument::Argument(const llvm::Argument& arg): Variable(ARGUMENT), argument(arg){}

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

    //InstructionVariable
    InstructionVariable::InstructionVariable(const llvm::Instruction& instv): Variable(INSTRUCTION_VARIABLE), instructionVariable(instv){}

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

    //Integer
    IntegerLiteral::IntegerLiteral(const llvm::ConstantInt& ci): Literal<int>(INTEGER_LITERAL), constInt(ci){}

    int IntegerLiteral::getValue(){
        return (int)constInt.getValue().getLimitedValue();
    }

    const llvm::ConstantInt &IntegerLiteral::unwrap(){
        return constInt;
    }

    //String
    StringLiteral::StringLiteral(const llvm::ConstantDataSequential & cs): Literal<std::string>(STRING_LITERAL), constSeq(cs){}

    std::string StringLiteral::getValue(){
        return constSeq.getAsString().str();
    }

    const llvm::ConstantDataSequential &StringLiteral::unwrap(){
        return constSeq;
    }

    //Boolean
    BooleanLiteral::BooleanLiteral(bool b): Literal<bool>(BOOLEAN_LITERAL), constBool(b){}

    bool BooleanLiteral::getValue(){
        return constBool;
    }

    //Memory Address
    MemoryAddress::MemoryAddress(const llvm::Value* ptr, const llvm::Value* idx, unsigned long sz): Value(MEMORY_ADDRESS), pointer(ptr) , index(idx), size(sz){}

    MemoryAddress::MemoryAddress(const llvm::Value* ptr, unsigned long sz): Value(MEMORY_ADDRESS), pointer(ptr), size(sz){}

    const llvm::Value* MemoryAddress::getPointer(){
        return pointer;
    }

    const llvm::Value* MemoryAddress::getIndex(){
        return index;
    }

    unsigned long MemoryAddress::getSize(){
        return size;
    }

}