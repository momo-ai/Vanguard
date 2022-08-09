#include "Value.h"
#include "LLVMtoVanguard.h"

namespace vanguard{
    // Global Variable 
    GlobalVariable::GlobalVariable(llvm::GlobalVariable& gv): globalVariable(gv){}

    Type* GlobalVariable::getType(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateType(*globalVariable.getType());
    }

    bool GlobalVariable::hasName(){
        return globalVariable.hasName();
    }

    std::string GlobalVariable::getName(){
        return std::string(globalVariable.getName());
    }

    //Argument
    Argument::Argument(llvm::Argument& arg): argument(arg){}

    Type* Argument::getType(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateType(*argument.getType());
    }

    bool Argument::hasName(){
        return argument.hasName();
    }

    std::string Argument::getName(){
        return std::string(argument.getName());
    }

    //InstructionVariable
    InstructionVariable::InstructionVariable(llvm::Instruction& instv): instructionVariable(instv){}

    Type* InstructionVariable::getType(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateType(*instructionVariable.getType());
    }

    bool InstructionVariable::hasName(){
        return instructionVariable.hasName();
    }

    std::string InstructionVariable::getName(){
        return std::string(instructionVariable.getName());
    }

    //Integer
    ConstantInteger::ConstantInteger(llvm::ConstantInt& ci): constInt(ci){}

    int ConstantInteger::getValue(){
        return constInt.getValue().getLimitedValue();
    }

    //String
    ConstantString::ConstantString(llvm::ConstantDataSequential & cs): constSeq(cs){}

    std::string ConstantString::getValue(){
        return constSeq.getAsString().str();
    }

    //Boolean
    ConstantBoolean::ConstantBoolean(bool b){
        constBool = b;
    }

    bool ConstantBoolean::getValue(){
        return constBool;
    }

}