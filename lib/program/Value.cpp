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

    llvm::GlobalVariable* GlobalVariable::unwrap(){
        return &globalVariable;
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

    llvm::Argument* Argument::unwrap(){
        return &argument;
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

    llvm::Instruction* InstructionVariable::unwrap(){
        return &instructionVariable;
    }

    //Integer
    ConstantInteger::ConstantInteger(llvm::ConstantInt& ci): constInt(ci){}

    int ConstantInteger::getValue(){
        return constInt.getValue().getLimitedValue();
    }

    llvm::ConstantInt* ConstantInteger::unwrap(){
        return &constInt;
    }

    //String
    ConstantString::ConstantString(llvm::ConstantDataSequential & cs): constSeq(cs){}

    std::string ConstantString::getValue(){
        return constSeq.getAsString().str();
    }

    llvm::ConstantDataSequential* ConstantString::unwrap(){
        return &constSeq;
    }

    //Boolean
    ConstantBoolean::ConstantBoolean(bool b){
        constBool = b;
    }

    bool ConstantBoolean::getValue(){
        return constBool;
    }

    //Memory Address
    MemoryAddress::MemoryAddress(llvm::Value* ptr, llvm::Value* idx, unsigned sz): pointer(ptr) , index(idx), size(sz){}

    llvm::Value* MemoryAddress::getPointer(){
        return pointer;
    }

    llvm::Value* MemoryAddress::getIndex(){
        return index;
    }

    unsigned MemoryAddress::getSize(){
        return size;
    }

}