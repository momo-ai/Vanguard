#include "Value.h"
#include "LLVMtoVanguard.h"

namespace vanguard{
    // Global Variable
    GlobalVariable::GlobalVariable(const llvm::GlobalVariable& gv): globalVariable(gv){}

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
    Argument::Argument(const llvm::Argument& arg): argument(arg){}

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
    InstructionVariable::InstructionVariable(const llvm::Instruction& instv): instructionVariable(instv){}

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
    IntegerLiteral::IntegerLiteral(const llvm::ConstantInt& ci): constInt(ci){}

    int IntegerLiteral::getValue(){
        return constInt.getValue().getLimitedValue();
    }

    const llvm::ConstantInt &IntegerLiteral::unwrap(){
        return constInt;
    }

    //String
    StringLiteral::StringLiteral(const llvm::ConstantDataSequential & cs): constSeq(cs){}

    std::string StringLiteral::getValue(){
        return constSeq.getAsString().str();
    }

    const llvm::ConstantDataSequential &StringLiteral::unwrap(){
        return constSeq;
    }

    //Boolean
    BooleanLiteral::BooleanLiteral(bool b){
        constBool = b;
    }

    bool BooleanLiteral::getValue(){
        return constBool;
    }

    //Memory Address
    MemoryAddress::MemoryAddress(const llvm::Value* ptr, const llvm::Value* idx, unsigned long sz): pointer(ptr) , index(idx), size(sz){}

    MemoryAddress::MemoryAddress(const llvm::Value* ptr, unsigned long sz): pointer(ptr), size(sz){}

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