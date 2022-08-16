#include "InstructionClasses.h"
#include "LLVMtoVanguard.h"

namespace vanguard{
    // Binary Operator
    BinaryOperator::BinaryOperator(const llvm::Instruction &inst, const llvm::BinaryOperator &bop)
            : BinaryOpInstruction(inst), binOp(bop) {}

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

    const llvm::BinaryOperator &BinaryOperator::unwrap(){
        return binOp;
    }


    //Compare Instruction
    CmpInst::CmpInst(const llvm::Instruction &inst, const llvm::CmpInst &cmpinst) : BinaryOpInstruction(inst),
                                                                                    cmpInst(cmpinst) {}

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

    const llvm::CmpInst &CmpInst::unwrap(){
        return cmpInst;
    }

    //Branch Inst
    BranchInst::BranchInst(const llvm::Instruction &inst, const llvm::BranchInst &brInst) : BranchInstruction(inst),
                                                                                            branchInst(brInst) {}

    bool BranchInst::isConditional(){
        return branchInst.isConditional();
    }

    Value* BranchInst::getCondition(){
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(branchInst.getCondition());
    }

    std::list<Block*> BranchInst::getSuccessors(){
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Block*> successors = {};
        unsigned int n = branchInst.getNumSuccessors();
        for(unsigned int i = 0; i < n; i++){
            successors.push_back(llvmToVanguard.translateBlock(branchInst.getSuccessor(i)));
        }
        return successors;
    }

    const llvm::BranchInst &BranchInst::unwrap(){
        return branchInst;
    }

    //Indirect Branch Instruction
    IndirectBrInst::IndirectBrInst(const llvm::Instruction &inst, const llvm::IndirectBrInst &ibrInst)
            : BranchInstruction(inst), indirectBrInst(ibrInst) {}

    Value* IndirectBrInst::getCondition(){
        throw std::runtime_error("Indirect Branch Instruction does not have a condition.");
    }

    std::list<Block*> IndirectBrInst::getSuccessors(){
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Block*> successors = {};
        unsigned int n = indirectBrInst.getNumSuccessors();
        for(unsigned int i = 0; i < n; i++){
            successors.push_back(llvmToVanguard.translateBlock(indirectBrInst.getSuccessor(i)));
        }
        return successors;
    }

    const llvm::IndirectBrInst &IndirectBrInst::unwrap(){
        return indirectBrInst;
    }

    //Switch Instruction
    SwitchInst::SwitchInst(const llvm::Instruction &inst, const llvm::SwitchInst &swInst) : BranchInstruction(inst),
                                                                                            switchInst(swInst) {}

    Value* SwitchInst::getCondition(){
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(switchInst.getCondition());
    }

    std::list<Block*> SwitchInst::getSuccessors(){
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Block*> successors = {};
        unsigned int n = switchInst.getNumSuccessors();
        for(unsigned int i = 0; i < n; i++){
            successors.push_back(llvmToVanguard.translateBlock(switchInst.getSuccessor(i)));
        }
        return successors;
    }

    const llvm::SwitchInst &SwitchInst::unwrap(){
        return switchInst;
    }

    //Unary Operator
    UnaryOperator::UnaryOperator(const llvm::Instruction &inst, const llvm::UnaryOperator &uop) : UnaryOpInstruction(
            inst), unaryOperator(uop) {}

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
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(unaryOperator.getOperand(0));
    }

    const llvm::UnaryOperator &UnaryOperator::unwrap(){
        return unaryOperator;
    }


    //Call
    Call::Call(const llvm::Instruction &inst, const llvm::CallBase &cb) : CallInstruction(inst), call(cb) {}

    Function* Call::getTarget(){
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateFunction(call.getFunction());
    }

    std::list<Value*> Call::getArgs(){
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Value*> args = {};
        for(auto itr = call.arg_begin(); itr != call.arg_end(); itr++){
            args.push_back(llvmToVanguard.translateValue(*itr));
        }
        return args;
    }

    const llvm::CallBase &Call::unwrap(){
        return call;
    }


    //Unreachable Instruction
    UnreachableInstruction::UnreachableInstruction(const llvm::Instruction &inst, const llvm::UnreachableInst &ui)
            : ErrorInstruction(inst), unreachableInstruction(ui) {}

    std::string UnreachableInstruction::error(){
        return "This instruction is unreachable.";
    }

    const llvm::UnreachableInst &UnreachableInstruction::unwrap(){
        return unreachableInstruction;
    }

    //Return Inst
    ReturnInst::ReturnInst(const llvm::Instruction &inst, const llvm::ReturnInst &retInst) : ReturnInstruction(inst),
                                                                                             returnInst(retInst) {}

    bool ReturnInst::returnsValue(){
        if (returnInst.getNumOperands() == 0) return false;
        else return true;
    }

    Value* ReturnInst::returnValue(){
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(returnInst.getReturnValue());
    }

    const llvm::ReturnInst &ReturnInst::unwrap(){
        return returnInst;
    }

    //Select Inst
    SelectInst::SelectInst(const llvm::Instruction &inst, const llvm::SelectInst &si) : MemoryReadInstruction(inst),
                                                                                        selectInst(si) {}

    InstructionVariable* SelectInst::getLHS(){
        InstructionVariable* instvar = new InstructionVariable(selectInst);
        return instvar;
    }

    const llvm::SelectInst &SelectInst::unwrap(){
        return selectInst;
    }

    //Extract Element Inst
    ExtractElementInst::ExtractElementInst(const llvm::Instruction &inst, const llvm::ExtractElementInst &eei)
            : MemoryReadInstruction(inst), extractElementInst(eei) {}

    InstructionVariable* ExtractElementInst::getLHS(){
        InstructionVariable* instvar = new InstructionVariable(extractElementInst);
        return instvar;
    }

    const llvm::ExtractElementInst &ExtractElementInst::unwrap(){
        return extractElementInst;
    }

    //Insert Value Inst
    InsertValueInst::InsertValueInst(const llvm::Instruction &inst, const llvm::InsertValueInst &ivi)
            : MemoryWriteInstruction(inst), insertValueInst(ivi) {}

    MemoryAddress* InsertValueInst::getMemoryAddress(){
        MemoryAddress* memAd = new MemoryAddress(insertValueInst.getOperand(0), insertValueInst.getOperand(2), sizeof(insertValueInst.getOperand(1)->getType()));
        return memAd;
    }

    const llvm::InsertValueInst &InsertValueInst::unwrap(){
        return insertValueInst;
    }

    //Insert Element Inst
    InsertElementInst::InsertElementInst(const llvm::Instruction &inst, const llvm::InsertElementInst &iei)
            : MemoryWriteInstruction(inst), insertElementInst(iei) {}

    MemoryAddress* InsertElementInst::getMemoryAddress(){
        MemoryAddress* memAd = new MemoryAddress(insertElementInst.getOperand(0), insertElementInst.getOperand(2), sizeof(insertElementInst.getOperand(1)->getType()));
        return memAd;
    }

    const llvm::InsertElementInst &InsertElementInst::unwrap(){
        return insertElementInst;
    }

    //Store Inst
    StoreInst::StoreInst(const llvm::Instruction &inst, const llvm::StoreInst &si) : MemoryWriteInstruction(inst),
                                                                                     storeInst(si) {}

    MemoryAddress* StoreInst::getMemoryAddress(){
        MemoryAddress* memAd = new MemoryAddress(storeInst.getPointerOperand(), sizeof(storeInst.getValueOperand()->getType()));
        return memAd;
    }

    const llvm::StoreInst &StoreInst::unwrap(){
        return storeInst;
    }

    //Shuffule Vector Inst
    ShuffleVectorInst::ShuffleVectorInst(const llvm::Instruction &inst, const llvm::ShuffleVectorInst &svi)
            : MemoryWriteInstruction(inst), shuffleVectorInst(svi) {}

    MemoryAddress* ShuffleVectorInst::getMemoryAddress(){
        MemoryAddress* memAd = new MemoryAddress(shuffleVectorInst.getOperand(2), sizeof(shuffleVectorInst.getOperand(2)));
        return memAd;
    }

    const llvm::ShuffleVectorInst &ShuffleVectorInst::unwrap(){
        return shuffleVectorInst;
    }

    //PHI Node
    PHINode::PHINode(const llvm::Instruction &inst, const llvm::PHINode &phin) : AssignInst(inst), phiNode(phin) {}

    InstructionVariable* PHINode::getLHS(){
        InstructionVariable* instvar = new InstructionVariable(phiNode);
        return instvar;
    }

    const llvm::PHINode &PHINode::unwrap(){
        return phiNode;
    }

    //Get element pointer
    GetElementPtrInst::GetElementPtrInst(const llvm::Instruction &inst, const llvm::GetElementPtrInst &gepi)
            : AssignInst(inst), getElementPtrInst(gepi) {}

    InstructionVariable* GetElementPtrInst::getLHS(){
        InstructionVariable* instvar = new InstructionVariable(getElementPtrInst);
        return instvar;
    }

    const llvm::GetElementPtrInst &GetElementPtrInst::unwrap(){
        return getElementPtrInst;
    }

    BinaryOpInstruction::BinaryOpInstruction(const llvm::Instruction &inst) : Instruction(inst) {

    }

    BranchInstruction::BranchInstruction(const llvm::Instruction &inst) : Instruction(inst) {

    }

    UnaryOpInstruction::UnaryOpInstruction(const llvm::Instruction &inst) : Instruction(inst) {

    }

    CallInstruction::CallInstruction(const llvm::Instruction &inst) : Instruction(inst) {

    }

    ErrorInstruction::ErrorInstruction(const llvm::Instruction &inst) : Instruction(inst) {

    }

    std::string ErrorInstruction::error() {
        return "";
    }

    ReturnInstruction::ReturnInstruction(const llvm::Instruction &inst) : Instruction(inst) {

    }

    AssignInstruction::AssignInstruction(const llvm::Instruction &inst) : Instruction(inst) {

    }

    MemoryReadInstruction::MemoryReadInstruction(const llvm::Instruction &inst) : AssignInstruction(inst) {

    }

    MemoryWriteInstruction::MemoryWriteInstruction(const llvm::Instruction &inst) : AssignInstruction(inst) {

    }

    AssignInst::AssignInst(const llvm::Instruction &inst) : AssignInstruction(inst) {

    }
}