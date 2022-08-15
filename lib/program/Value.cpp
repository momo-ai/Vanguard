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

    //Integer
    IntegerLiteral::IntegerLiteral(const llvm::ConstantInt& ci): constInt(ci){}

    int IntegerLiteral::getValue(){
        return constInt.getValue().getLimitedValue();
    }

    //String
    StringLiteral::StringLiteral(const llvm::ConstantDataSequential & cs): constSeq(cs){}

    std::string StringLiteral::getValue(){
        return constSeq.getAsString().str();
    }

}