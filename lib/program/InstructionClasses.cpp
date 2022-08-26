#include "InstructionClasses.h"
#include "LLVMtoVanguard.h"

namespace vanguard{

    // Binary Operator
    BinaryOperator::BinaryOperator(const llvm::BinaryOperator &bop) : InstructionClass<llvm::BinaryOperator>(BINARY_OPERATOR, bop), binOp(bop) {}

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
        auto* instvar = new InstructionVariable(binOp);
        return instvar;
    }

    const llvm::BinaryOperator &BinaryOperator::unwrap(){
        return binOp;
    }


    //Compare Instruction
    CmpInst::CmpInst(const llvm::CmpInst &cmpinst) : InstructionClass<llvm::CmpInst>(CMP_INST, cmpinst), cmpInst(cmpinst) {}

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
        auto* instvar = new InstructionVariable(cmpInst);
        return instvar;
    }

    const llvm::CmpInst &CmpInst::unwrap(){
        return cmpInst;
    }

    //Branch Inst
    BranchInst::BranchInst(const llvm::BranchInst &brInst) : InstructionClass<llvm::BranchInst>(BRANCH_INST,brInst), branchInst(brInst) {}

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
    IndirectBrInst::IndirectBrInst(const llvm::IndirectBrInst &ibrInst) : InstructionClass<llvm::IndirectBrInst>(INDIRECT_BR_INST,ibrInst), indirectBrInst(ibrInst) {}

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
    SwitchInst::SwitchInst(const llvm::SwitchInst &swInst) : InstructionClass<llvm::SwitchInst>(SWITCH_INST, swInst), switchInst(swInst) {}

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
    UnaryOperator::UnaryOperator(const llvm::UnaryOperator &uop) : InstructionClass<llvm::UnaryOperator>(UNARY_OPERATOR,uop), unaryOperator(uop) {}

    unsigned UnaryOperator::getOpClass(){
        unsigned opcode = unaryOperator.getOpcode();
        UnaryOpClass unaryOpClass;
        if (opcode == 12) unaryOpClass = Neg;
        else{
            throw std::runtime_error("The opcode "+ std::string(unaryOperator.getOpcodeName())+ " is not a unary operator class in Vanguard.");
        }
        return unaryOpClass;
    }

    Value* UnaryOperator::getUnaryOperand() {
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(unaryOperator.getOperand(0));
    }

    const llvm::UnaryOperator &UnaryOperator::unwrap(){
        return unaryOperator;
    }

    //Cast Instruction
    CastInst::CastInst(const llvm::CastInst &ci): InstructionClass<llvm::CastInst>(CAST_INST,ci), castInst(ci){}

    unsigned CastInst::getOpClass() {
        unsigned opcode = castInst.getOpcode();
        CastInstClass castInstClass;
        if (opcode == 38) castInstClass = Trunc;
        else if(opcode == 39) castInstClass = ZExt;
        else if(opcode == 40) castInstClass = SExt;
        else if(41 <= opcode && opcode <= 46) castInstClass = FPCasts;
        else if(opcode == 47) castInstClass = PtrToInt;
        else if (opcode == 48) castInstClass = IntToPtr;
        else if (opcode == 49) castInstClass = BitCast;
        else if (opcode == 50) castInstClass = AddrSpaceCast;
        else{
            throw std::runtime_error("The opcode "+ std::string(castInst.getOpcodeName()) + " is not a unary cast operator class in vanguard.");
        }
        return castInstClass;
    }

    Value* CastInst::getUnaryOperand() {
        LLVMtoVanguard &llvMtoVanguard = LLVMtoVanguard::getInstance();
        return llvMtoVanguard.translateValue(castInst.getOperand(0));
    }

    const llvm::CastInst &CastInst::unwrap() {
        return castInst;
    }

    //Call
    Call::Call(const llvm::CallBase &cb) : InstructionClass<llvm::CallBase>(CALL, cb), call(cb) {}

    Function* Call::getTarget(){
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateFunction(call.getCalledFunction());
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
    UnreachableInstruction::UnreachableInstruction(const llvm::UnreachableInst &ui)
            : InstructionClass<llvm::UnreachableInst>(UNREACHABLE_INSTRUCTION, ui), unreachableInstruction(ui) {}

    std::string UnreachableInstruction::error(){
        return "This instruction is unreachable.";
    }

    const llvm::UnreachableInst &UnreachableInstruction::unwrap(){
        return unreachableInstruction;
    }

    //Return Inst
    ReturnInst::ReturnInst(const llvm::ReturnInst &retInst) : InstructionClass<llvm::ReturnInst>(RETURN_INST, retInst),
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
    SelectInst::SelectInst(const llvm::SelectInst &si) : InstructionClass<llvm::SelectInst>(SELECT_INST, si),
                                                                                        selectInst(si) {}

    InstructionVariable* SelectInst::getLHS(){
        auto* instvar = new InstructionVariable(selectInst);
        return instvar;
    }

    const llvm::SelectInst &SelectInst::unwrap(){
        return selectInst;
    }

    //Extract Element Inst
    ExtractElementInst::ExtractElementInst(const llvm::ExtractElementInst &eei)
            : InstructionClass<llvm::ExtractElementInst>(EXTRACT_ELEMENT_INST, eei), extractElementInst(eei) {}

    InstructionVariable* ExtractElementInst::getLHS(){
        auto* instvar = new InstructionVariable(extractElementInst);
        return instvar;
    }

    const llvm::ExtractElementInst &ExtractElementInst::unwrap(){
        return extractElementInst;
    }

    //Extract Value Inst
    ExtractValueInst::ExtractValueInst(const llvm::ExtractValueInst &evi)
            : InstructionClass<llvm::ExtractValueInst>(EXTRACT_VALUE_INST, evi), extractValueInst(evi) {}

    InstructionVariable* ExtractValueInst::getLHS(){
        auto* instvar = new InstructionVariable(extractValueInst);
        return instvar;
    }

    const llvm::ExtractValueInst &ExtractValueInst::unwrap(){
        return extractValueInst;
    }

    //Load Instruction
    LoadInst::LoadInst(const llvm::LoadInst &li): InstructionClass<llvm::LoadInst>(LOAD_INST, li), loadInst(li) {}

    Value *LoadInst::getUnaryOperand() {
        LLVMtoVanguard &llvMtoVanguard = LLVMtoVanguard::getInstance();
        return llvMtoVanguard.translateValue(loadInst.getOperand(0));
    }

    InstructionVariable* LoadInst::getLHS(){
        auto* instvar = new InstructionVariable(loadInst);
        return instvar;
    }

    const llvm::LoadInst &LoadInst::unwrap() {
        return loadInst;
    }

    //Insert Value Inst
    InsertValueInst::InsertValueInst(const llvm::InsertValueInst &ivi)
            : InstructionClass<llvm::InsertValueInst>(INSERT_VALUE_INST, ivi), insertValueInst(ivi) {}

    MemoryAddress* InsertValueInst::getMemoryAddress(){
        auto* memAd = new MemoryAddress(insertValueInst.getOperand(0), insertValueInst.getOperand(2), sizeof(insertValueInst.getOperand(1)->getType()));
        return memAd;
    }

    const llvm::InsertValueInst &InsertValueInst::unwrap(){
        return insertValueInst;
    }

    //Insert Element Inst
    InsertElementInst::InsertElementInst(const llvm::InsertElementInst &iei)
            : InstructionClass<llvm::InsertElementInst>(INSERT_ELEMENT_INST, iei), insertElementInst(iei) {}

    MemoryAddress* InsertElementInst::getMemoryAddress(){
        auto* memAd = new MemoryAddress(insertElementInst.getOperand(0), insertElementInst.getOperand(2), sizeof(insertElementInst.getOperand(1)->getType()));
        return memAd;
    }

    const llvm::InsertElementInst &InsertElementInst::unwrap(){
        return insertElementInst;
    }

    //Store Inst
    StoreInst::StoreInst(const llvm::StoreInst &si) : InstructionClass<llvm::StoreInst>(STORE_INST, si),
                                                                                     storeInst(si) {}

    MemoryAddress* StoreInst::getMemoryAddress(){
        auto* memAd = new MemoryAddress(storeInst.getPointerOperand(), sizeof(storeInst.getValueOperand()->getType()));
        return memAd;
    }

    const llvm::StoreInst &StoreInst::unwrap(){
        return storeInst;
    }

    //Shuffule Vector Inst
    ShuffleVectorInst::ShuffleVectorInst(const llvm::ShuffleVectorInst &svi)
            : InstructionClass<llvm::ShuffleVectorInst>(SHUFFLE_VECTOR_INST, svi), shuffleVectorInst(svi) {}

    MemoryAddress* ShuffleVectorInst::getMemoryAddress(){
        auto* memAd = new MemoryAddress(shuffleVectorInst.getOperand(2), sizeof(shuffleVectorInst.getOperand(2)));
        return memAd;
    }

    const llvm::ShuffleVectorInst &ShuffleVectorInst::unwrap(){
        return shuffleVectorInst;
    }

    //Alloca Instruction
    AllocaInst::AllocaInst(const llvm::AllocaInst &ai): InstructionClass<llvm::AllocaInst>(ALLOCA_INST, ai), allocaInst(ai) {}

    Value *AllocaInst::getUnaryOperand() {
        LLVMtoVanguard &llvMtoVanguard = LLVMtoVanguard::getInstance();
        return llvMtoVanguard.translateValue(allocaInst.getOperand(0));
    }

    MemoryAddress* AllocaInst::getMemoryAddress() {
        auto* memAd = new MemoryAddress(allocaInst.getOperand(0), sizeof(allocaInst.getOperand(0)));
        return memAd;
    }

    const llvm::AllocaInst &AllocaInst::unwrap() {
        return allocaInst;
    }

    //PHI Node
    PHINode::PHINode(const llvm::PHINode &phin) : InstructionClass<llvm::PHINode>(PHI_NODE, phin), phiNode(phin) {}

    InstructionVariable* PHINode::getLHS(){
        auto* instvar = new InstructionVariable(phiNode);
        return instvar;
    }

    const llvm::PHINode &PHINode::unwrap(){
        return phiNode;
    }

    //Get element pointer
    GetElementPtrInst::GetElementPtrInst(const llvm::GetElementPtrInst &gepi)
            : InstructionClass<llvm::GetElementPtrInst>(GET_ELEMENT_PTR_INST, gepi), getElementPtrInst(gepi) {}

    InstructionVariable* GetElementPtrInst::getLHS(){
        auto* instvar = new InstructionVariable(getElementPtrInst);
        return instvar;
    }

    const llvm::GetElementPtrInst &GetElementPtrInst::unwrap(){
        return getElementPtrInst;
    }

    //Freeze Instruction
    FreezeInst::FreezeInst(const llvm::FreezeInst &fi): InstructionClass<llvm::FreezeInst>(FREEZE_INST, fi), freezeInst(fi) {}

    Value *FreezeInst::getUnaryOperand() {
        LLVMtoVanguard &llvMtoVanguard = LLVMtoVanguard::getInstance();
        return llvMtoVanguard.translateValue(freezeInst.getOperand(0));
    }

    const llvm::FreezeInst &FreezeInst::unwrap() {
        return freezeInst;
    }

    InstructionVariable* FreezeInst::getLHS(){
        auto* instvar = new InstructionVariable(freezeInst);
        return instvar;
    }

}