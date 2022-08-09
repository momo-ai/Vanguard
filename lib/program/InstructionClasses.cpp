#include "InstructionClasses.h"
#include "LLVMtoVanguard.h"

namespace vanguard{
    // Binary Operator
    BinaryOperator::BinaryOperator(llvm::BinaryOperator& bop): binOp(bop){}

    unsigned BinaryOperator::getOpClass() {
        unsigned opcode = binOp.getOpcode();
        BinaryOpClass binaryOpClass;
        if (opcode == 13 || opcode == 14) binaryOpClass = Add;
        else if(opcode == 15 || opcode == 16) binaryOpClass = Sub;
        else if(opcode == 17 || opcode == 18) binaryOpClass = Mul;
        else if (opcode == 19 || opcode == 20 || opcode == 21) binaryOpClass = Div;
        else if (opcode == 22 || opcode == 23 || opcode == 24) binaryOpClass = Mod;
        else if (opcode == 25)  binaryOpClass = Shl;
        else if (opcode == 26 || opcode == 27) binaryOpClass = Shr;
        else if (opcode == 28) binaryOpClass = And;
        else if (opcode == 29) binaryOpClass = Or;
        else if (opcode == 30) binaryOpClass = Xor;
        else{
            throw std::runtime_error("The opcode "+ std::string(binOp.getOpcodeName()) + " is not a binary operator class in vanguard.");
        }
        return binaryOpClass;
    }

    InstructionVariable* BinaryOperator::getLHS(){
        InstructionVariable* instvar = new InstructionVariable(binOp);
        return instvar;
    }

    Value* BinaryOperator::getRHS(){
        ConstantBoolean* b = new ConstantBoolean(true);
        return b;
    }

    //Compare Instruction
    CmpInst::CmpInst(llvm::CmpInst& cmpinst): cmpInst(cmpinst){}

    unsigned CmpInst::getOpClass(){
        unsigned opcode = cmpInst.getOpcode();
        BinaryOpClass binaryOpClass;
        if (opcode == 53 || opcode == 54) binaryOpClass = IFCmpInst;
        else {
            throw std::runtime_error("The opcode "+ std::string(cmpInst.getOpcodeName()) + " is not a cmp operator class in vanguard.");
        }
        return  binaryOpClass;
    }

    InstructionVariable* CmpInst::getLHS(){
        InstructionVariable* instvar = new InstructionVariable(cmpInst);
        return instvar;
    }

    Value* CmpInst::getRHS(){
        ConstantBoolean* b = new ConstantBoolean(true);
        return b;
    }

    //Branch Inst
    BranchInst::BranchInst(llvm::BranchInst& brInst): branchInst(brInst){}

    bool BranchInst::isConditional(){
        return branchInst.isConditional();
    }

    Value* BranchInst::getCondition(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateValue(branchInst.getCondition());
    }

    std::list<Block*> BranchInst::getSuccessors(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Block*> successors = {};
        int n = branchInst.getNumSuccessors();
        for(int i = 0; i < n; i++){
            successors.push_back(llvmToVanguard->translateBlock(branchInst.getSuccessor(i)));
        }
        return successors;
    }

    //Indirect Branch Instruction
    IndirectBrInst::IndirectBrInst(llvm::IndirectBrInst& ibrInst): indirectBrInst(ibrInst){}

    Value* IndirectBrInst::getCondition(){
        throw std::runtime_error("Indirect Branch Instruction does not have a condition.");
        return nullptr;
    }

    std::list<Block*> IndirectBrInst::getSuccessors(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Block*> successors = {};
        int n = indirectBrInst.getNumSuccessors();
        for(int i = 0; i < n; i++){
            successors.push_back(llvmToVanguard->translateBlock(indirectBrInst.getSuccessor(i)));
        }
        return successors;
    }

    //Switch Instruction
    SwitchInst::SwitchInst(llvm::SwitchInst& swInst): switchInst(swInst){}

    Value* SwitchInst::getCondition(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateValue(switchInst.getCondition());
    }

    std::list<Block*> SwitchInst::getSuccessors(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Block*> successors = {};
        int n = switchInst.getNumSuccessors();
        for(int i = 0; i < n; i++){
            successors.push_back(llvmToVanguard->translateBlock(switchInst.getSuccessor(i)));
        }
        return successors;
    }

    //Unary Operator
    UnaryOperator::UnaryOperator(llvm::UnaryOperator& uop): unaryOperator(uop){}

    unsigned UnaryOperator::getOpClass(){
        unsigned opcode = unaryOperator.getOpcode();
        UnaryOpClass unaryOpClass;
        if (opcode == 12) unaryOpClass = Neg;
        else{
            throw std::runtime_error("The opcode "+ std::string(unaryOperator.getOpcodeName())+ " is not a unary operator class in Vanguard.");
        }
        return unaryOpClass;
    }

    Value* UnaryOperator::getOperand(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateValue(unaryOperator.getOperand(0));
    }


    //Call 
    Call::Call(llvm::CallBase& cb): call(cb){}

    Function* Call::getTarget(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateFunction(call.getFunction());
    }

    std::list<Value*> Call::getArgs(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Value*> args = {};
        for(auto itr = call.arg_begin(); itr != call.arg_end(); itr++){
            args.push_back(llvmToVanguard->translateValue(*itr));
        }
        return args;
    }


    //Unreachable Instruction
    UnreachableInstruction::UnreachableInstruction(llvm::UnreachableInst& ui): unreachableInstruction(ui){}

    std::string UnreachableInstruction::error(){
        return "This instruction is unreachable.";
    }

    //Return Inst
    ReturnInst::ReturnInst(llvm::ReturnInst& retInst): returnInst(retInst){}

    bool ReturnInst::returnsValue(){
        if (returnInst.getNumOperands() == 0) return false;
        else return true;
    }

    Value* ReturnInst::returnValue(){
        LLVMtoVanguard* llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard->translateValue(returnInst.getReturnValue());
    }

    //Select Inst
    SelectInst::SelectInst(llvm::SelectInst& si): selectInst(si){}

    InstructionVariable* SelectInst::getLHS(){
        InstructionVariable* instvar = new InstructionVariable(selectInst);
        return instvar;
    }

    Value* SelectInst::getRHS(){
        ConstantBoolean* b = new ConstantBoolean(true);
        return b;
    }

    //Extract Element Inst
    ExtractElementInst::ExtractElementInst(llvm::ExtractElementInst& eei): extractElementInst(eei){}

    InstructionVariable* ExtractElementInst::getLHS(){
        InstructionVariable* instvar = new InstructionVariable(extractElementInst);
        return instvar;
    }

    Value* ExtractElementInst::getRHS(){
        ConstantBoolean* b = new ConstantBoolean(true);
        return b;
    }

    //Insert Value Inst
    InsertValueInst::InsertValueInst(llvm::InsertValueInst& ivi): insertValueInst(ivi){}

    InstructionVariable* InsertValueInst::getLHS(){
        InstructionVariable* instvar = new InstructionVariable(insertValueInst);
        return instvar;
    }

    Value* InsertValueInst::getRHS(){
        ConstantBoolean* b = new ConstantBoolean(true);
        return b;
    }

    //Insert Element Inst
    InsertElementInst::InsertElementInst(llvm::InsertElementInst& iei): insertElementInst(iei){}

    InstructionVariable* InsertElementInst::getLHS(){
        InstructionVariable* instvar = new InstructionVariable(insertElementInst);
        return instvar;
    }

    Value* InsertElementInst::getRHS(){
        ConstantBoolean* b = new ConstantBoolean(true);
        return b;
    }

    //Store Inst
    StoreInst::StoreInst(llvm::StoreInst& si): storeInst(si){}

    InstructionVariable* StoreInst::getLHS(){
        InstructionVariable* instvar = new InstructionVariable(storeInst);
        return instvar;
    }

    Value* StoreInst::getRHS(){
        ConstantBoolean* b = new ConstantBoolean(true);
        return b;
    }

    //Shuffule Vector Inst
    ShuffleVectorInst::ShuffleVectorInst(llvm::ShuffleVectorInst& svi): shuffleVectorInst(svi){}

    InstructionVariable* ShuffleVectorInst::getLHS(){
        InstructionVariable* instvar = new InstructionVariable(shuffleVectorInst);
        return instvar;
    }

    Value* ShuffleVectorInst::getRHS(){
        ConstantBoolean* b = new ConstantBoolean(true);
        return b;
    }

    //PHI Node
    PHINode::PHINode(llvm::PHINode& phin): phiNode(phin){}

    InstructionVariable* PHINode::getLHS(){
        InstructionVariable* instvar = new InstructionVariable(phiNode);
        return instvar;
    }

    Value* PHINode::getRHS(){
        ConstantBoolean* b = new ConstantBoolean(true);
        return b;
    }

    //Get element pointer
    GetElementPtrInst::GetElementPtrInst(llvm::GetElementPtrInst& gepi): getElemenPtrInst(gepi){}

    InstructionVariable* GetElementPtrInst::getLHS(){
        InstructionVariable* instvar = new InstructionVariable(getElemenPtrInst);
        return instvar;
    }

    Value* GetElementPtrInst::getRHS(){
        ConstantBoolean* b = new ConstantBoolean(true);
        return b;
    }

}