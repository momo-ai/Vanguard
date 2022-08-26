#include "InstructionClasses.h"
#include "LLVMtoVanguard.h"

namespace vanguard{

    // Binary Operator
    BinaryOperator::BinaryOperator(const llvm::BinaryOperator &bop) : InstructionClass<llvm::BinaryOperator>(BINARY_OPERATOR, bop), binOp(bop) {}

    unsigned BinaryOperator::getOpClass() const {
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

    InstructionVariable* BinaryOperator::getLHS() const{
        auto* instvar = new InstructionVariable(binOp);
        return instvar;
    }

    const llvm::BinaryOperator &BinaryOperator::unwrap() const{
        return binOp;
    }

    void BinaryOperator::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }


    //Compare Instruction
    CmpInst::CmpInst(const llvm::CmpInst &cmpinst) : InstructionClass<llvm::CmpInst>(CMP_INST, cmpinst), cmpInst(cmpinst) {}

    unsigned CmpInst::getOpClass() const{
        unsigned opcode = cmpInst.getOpcode();
        BinaryOpClass binaryOpClass;
        if (opcode == 53 || opcode == 54) binaryOpClass = IFCmpInst;
        else {
            throw std::runtime_error("The opcode "+ std::string(cmpInst.getOpcodeName()) + " is not a cmp operator class in vanguard.");
        }
        return  binaryOpClass;
    }

    InstructionVariable* CmpInst::getLHS() const{
        auto* instvar = new InstructionVariable(cmpInst);
        return instvar;
    }

    const llvm::CmpInst &CmpInst::unwrap() const{
        return cmpInst;
    }

    void CmpInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }


    //Branch Inst
    BranchInst::BranchInst(const llvm::BranchInst &brInst) : InstructionClass<llvm::BranchInst>(BRANCH_INST,brInst), branchInst(brInst) {}

    bool BranchInst::isConditional() const{
        return branchInst.isConditional();
    }

    Value* BranchInst::getCondition() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(branchInst.getCondition());
    }

    std::list<Block*> BranchInst::getSuccessors() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Block*> successors = {};
        unsigned int n = branchInst.getNumSuccessors();
        for(unsigned int i = 0; i < n; i++){
            successors.push_back(llvmToVanguard.translateBlock(branchInst.getSuccessor(i)));
        }
        return successors;
    }

    const llvm::BranchInst &BranchInst::unwrap() const{
        return branchInst;
    }

    void BranchInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Indirect Branch Instruction
    IndirectBrInst::IndirectBrInst(const llvm::IndirectBrInst &ibrInst) : InstructionClass<llvm::IndirectBrInst>(INDIRECT_BR_INST,ibrInst), indirectBrInst(ibrInst) {}

    Value* IndirectBrInst::getCondition() const{
        throw std::runtime_error("Indirect Branch Instruction does not have a condition.");
    }

    std::list<Block*> IndirectBrInst::getSuccessors() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Block*> successors = {};
        unsigned int n = indirectBrInst.getNumSuccessors();
        for(unsigned int i = 0; i < n; i++){
            successors.push_back(llvmToVanguard.translateBlock(indirectBrInst.getSuccessor(i)));
        }
        return successors;
    }

    const llvm::IndirectBrInst &IndirectBrInst::unwrap() const{
        return indirectBrInst;
    }

    void IndirectBrInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Switch Instruction
    SwitchInst::SwitchInst(const llvm::SwitchInst &swInst) : InstructionClass<llvm::SwitchInst>(SWITCH_INST, swInst), switchInst(swInst) {}

    Value* SwitchInst::getCondition() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(switchInst.getCondition());
    }

    std::list<Block*> SwitchInst::getSuccessors() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Block*> successors = {};
        unsigned int n = switchInst.getNumSuccessors();
        for(unsigned int i = 0; i < n; i++){
            successors.push_back(llvmToVanguard.translateBlock(switchInst.getSuccessor(i)));
        }
        return successors;
    }

    const llvm::SwitchInst &SwitchInst::unwrap() const{
        return switchInst;
    }

    void SwitchInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Unary Operator
    UnaryOperator::UnaryOperator(const llvm::UnaryOperator &uop) : InstructionClass<llvm::UnaryOperator>(UNARY_OPERATOR,uop), unaryOperator(uop) {}

    unsigned UnaryOperator::getOpClass() const{
        unsigned opcode = unaryOperator.getOpcode();
        UnaryOpClass unaryOpClass;
        if (opcode == 12) unaryOpClass = Neg;
        else{
            throw std::runtime_error("The opcode "+ std::string(unaryOperator.getOpcodeName())+ " is not a unary operator class in Vanguard.");
        }
        return unaryOpClass;
    }

    Value* UnaryOperator::getUnaryOperand() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(unaryOperator.getOperand(0));
    }

    const llvm::UnaryOperator &UnaryOperator::unwrap() const{
        return unaryOperator;
    }

    void UnaryOperator::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Cast Instruction
    CastInst::CastInst(const llvm::CastInst &ci): InstructionClass<llvm::CastInst>(CAST_INST,ci), castInst(ci){}

    unsigned CastInst::getOpClass() const{
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

    Value* CastInst::getUnaryOperand() const{
        LLVMtoVanguard &llvMtoVanguard = LLVMtoVanguard::getInstance();
        return llvMtoVanguard.translateValue(castInst.getOperand(0));
    }

    Type* CastInst::getSrcType() const {
        LLVMtoVanguard &llvMtoVanguard = LLVMtoVanguard::getInstance();
        return llvMtoVanguard.translateType(castInst.getSrcTy());
    }

    Type* CastInst::getDestType() const {
        LLVMtoVanguard &llvMtoVanguard = LLVMtoVanguard::getInstance();
        return llvMtoVanguard.translateType(castInst.getDestTy());
    }

    const llvm::CastInst &CastInst::unwrap() const {
        return castInst;
    }

    void CastInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Call
    Call::Call(const llvm::CallBase &cb) : InstructionClass<llvm::CallBase>(CALL, cb), call(cb) {}

    Function* Call::getTarget() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateFunction(call.getFunction());
    }

    std::list<Value*> Call::getArgs() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Value*> args = {};
        for(auto itr = call.arg_begin(); itr != call.arg_end(); itr++){
            args.push_back(llvmToVanguard.translateValue(*itr));
        }
        return args;
    }

    const llvm::CallBase &Call::unwrap() const{
        return call;
    }

    void Call::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Unreachable Instruction
    UnreachableInstruction::UnreachableInstruction(const llvm::UnreachableInst &ui)
            : InstructionClass<llvm::UnreachableInst>(UNREACHABLE_INSTRUCTION, ui), unreachableInstruction(ui) {}

    std::string UnreachableInstruction::error() const{
        return "This instruction is unreachable.";
    }

    const llvm::UnreachableInst &UnreachableInstruction::unwrap() const{
        return unreachableInstruction;
    }

    void UnreachableInstruction::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Return Inst
    ReturnInst::ReturnInst(const llvm::ReturnInst &retInst) : InstructionClass<llvm::ReturnInst>(RETURN_INST, retInst),
                                                                                             returnInst(retInst) {}

    bool ReturnInst::returnsValue() const{
        if (returnInst.getNumOperands() == 0) return false;
        else return true;
    }

    Value* ReturnInst::returnValue() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(returnInst.getReturnValue());
    }

    const llvm::ReturnInst &ReturnInst::unwrap() const{
        return returnInst;
    }

    void ReturnInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Select Inst
    SelectInst::SelectInst(const llvm::SelectInst &si) : InstructionClass<llvm::SelectInst>(SELECT_INST, si),
                                                                                        selectInst(si) {}

    InstructionVariable* SelectInst::getLHS() const{
        auto* instvar = new InstructionVariable(selectInst);
        return instvar;
    }

    Value *SelectInst::getCondition() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(selectInst.getCondition());
    }

    Value *SelectInst::getTrueValue() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(selectInst.getTrueValue());
    }

    Value *SelectInst::getFalseValue() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(selectInst.getFalseValue());
    }

    const llvm::SelectInst &SelectInst::unwrap() const{
        return selectInst;
    }

    void SelectInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Extract Element Inst
    ExtractElementInst::ExtractElementInst(const llvm::ExtractElementInst &eei)
            : InstructionClass<llvm::ExtractElementInst>(EXTRACT_ELEMENT_INST, eei), extractElementInst(eei) {}

    InstructionVariable* ExtractElementInst::getLHS() const{
        auto* instvar = new InstructionVariable(extractElementInst);
        return instvar;
    }

    Value *ExtractElementInst::getVectorOperand() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(extractElementInst.getVectorOperand());
    }

    Value *ExtractElementInst::getIndexOperand() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(extractElementInst.getIndexOperand());
    }

    const llvm::ExtractElementInst &ExtractElementInst::unwrap() const{
        return extractElementInst;
    }

    void ExtractElementInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Extract Value Inst
    ExtractValueInst::ExtractValueInst(const llvm::ExtractValueInst &evi)
            : InstructionClass<llvm::ExtractValueInst>(EXTRACT_VALUE_INST, evi), extractValueInst(evi) {}

    InstructionVariable* ExtractValueInst::getLHS() const{
        auto* instvar = new InstructionVariable(extractValueInst);
        return instvar;
    }

    Value *ExtractValueInst::getAggregateOperand() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(extractValueInst.getAggregateOperand());
    }

    std::list<unsigned> ExtractValueInst::getIndices() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<unsigned> idxs = {};
        for (unsigned i: extractValueInst.indices()){
            idxs.push_back(i);
        }
        return idxs;
    }

    const llvm::ExtractValueInst &ExtractValueInst::unwrap() const{
        return extractValueInst;
    }

    void ExtractValueInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Load Instruction
    LoadInst::LoadInst(const llvm::LoadInst &li): InstructionClass<llvm::LoadInst>(LOAD_INST, li), loadInst(li) {}

    InstructionVariable* LoadInst::getLHS() const{
        auto* instvar = new InstructionVariable(loadInst);
        return instvar;
    }

    Value *LoadInst::getPointerOperand() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(loadInst.getPointerOperand());
    }

    Type *LoadInst::getPointerOperandType() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(loadInst.getPointerOperandType());
    }

    unsigned LoadInst::getSize() const{
        return loadInst.getPointerAddressSpace();
    }

    const llvm::LoadInst &LoadInst::unwrap() const {
        return loadInst;
    }

    void LoadInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Insert Value Inst
    InsertValueInst::InsertValueInst(const llvm::InsertValueInst &ivi)
            : InstructionClass<llvm::InsertValueInst>(INSERT_VALUE_INST, ivi), insertValueInst(ivi) {}

    Value *InsertValueInst::getAggregateOperand() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(insertValueInst.getAggregateOperand());
    }

    Value *InsertValueInst::getInsertedValueOperand() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(insertValueInst.getInsertedValueOperand());
    }

    std::list<unsigned> InsertValueInst::getIndices() const {
        std::list<unsigned> idxs = {};
        for(unsigned i: insertValueInst.indices()){
            idxs.push_back(i);
        }
        return idxs;
    }

    MemoryAddress* InsertValueInst::getMemoryAddress() const{
        auto* memAd = new MemoryAddress(insertValueInst.getOperand(0), insertValueInst.getOperand(2), sizeof(insertValueInst.getOperand(1)->getType()));
        return memAd;
    }

    const llvm::InsertValueInst &InsertValueInst::unwrap() const{
        return insertValueInst;
    }

    void InsertValueInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Insert Element Inst
    InsertElementInst::InsertElementInst(const llvm::InsertElementInst &iei)
            : InstructionClass<llvm::InsertElementInst>(INSERT_ELEMENT_INST, iei), insertElementInst(iei) {}

    Value *InsertElementInst::getVector() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(insertElementInst.getOperand(0));
    }

    Value *InsertElementInst::getInsertedElement() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(insertElementInst.getOperand(1));
    }

    Value *InsertElementInst::getIndex() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(insertElementInst.getOperand(2));
    }

    MemoryAddress* InsertElementInst::getMemoryAddress() const{
        auto* memAd = new MemoryAddress(insertElementInst.getOperand(0), insertElementInst.getOperand(2), sizeof(insertElementInst.getOperand(1)->getType()));
        return memAd;
    }

    const llvm::InsertElementInst &InsertElementInst::unwrap() const{
        return insertElementInst;
    }

    void InsertElementInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Store Inst
    StoreInst::StoreInst(const llvm::StoreInst &si) : InstructionClass<llvm::StoreInst>(STORE_INST, si),
                                                                                     storeInst(si) {}

    Value *StoreInst::getPointerOperand() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(storeInst.getPointerOperand());
    }

    Value *StoreInst::getValueOperand() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(storeInst.getValueOperand());
    }

    Type *StoreInst::getPointerOperandType() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(storeInst.getPointerOperandType());
    }

    unsigned StoreInst::getSize() const {
        return storeInst.getPointerAddressSpace();
    }

    MemoryAddress* StoreInst::getMemoryAddress() const{
        auto* memAd = new MemoryAddress(storeInst.getPointerOperand(), sizeof(storeInst.getValueOperand()->getType()));
        return memAd;
    }

    const llvm::StoreInst &StoreInst::unwrap() const{
        return storeInst;
    }

    void StoreInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Shuffule Vector Inst
    ShuffleVectorInst::ShuffleVectorInst(const llvm::ShuffleVectorInst &svi)
            : InstructionClass<llvm::ShuffleVectorInst>(SHUFFLE_VECTOR_INST, svi), shuffleVectorInst(svi) {}

    MemoryAddress* ShuffleVectorInst::getMemoryAddress() const{
        auto* memAd = new MemoryAddress(shuffleVectorInst.getOperand(2), sizeof(shuffleVectorInst.getOperand(2)));
        return memAd;
    }

    const llvm::ShuffleVectorInst &ShuffleVectorInst::unwrap() const{
        return shuffleVectorInst;
    }

    void ShuffleVectorInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Alloca Instruction
    AllocaInst::AllocaInst(const llvm::AllocaInst &ai): InstructionClass<llvm::AllocaInst>(ALLOCA_INST, ai), allocaInst(ai) {}

    Type *AllocaInst::getAllocatedType() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(allocaInst.getAllocatedType());
    }

    MemoryAddress* AllocaInst::getMemoryAddress() const{
        auto* memAd = new MemoryAddress(allocaInst.getOperand(0), sizeof(allocaInst.getOperand(0)));
        return memAd;
    }

    const llvm::AllocaInst &AllocaInst::unwrap() const{
        return allocaInst;
    }

    void AllocaInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //PHI Node
    PHINode::PHINode(const llvm::PHINode &phin) : InstructionClass<llvm::PHINode>(PHI_NODE, phin), phiNode(phin) {}

    InstructionVariable* PHINode::getLHS() const{
        auto* instvar = new InstructionVariable(phiNode);
        return instvar;
    }

    unsigned PHINode::getNumIncomingValues() const{
        return phiNode.getNumIncomingValues();
    }

    std::vector<Value *> PHINode::getIncomingValues() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::vector<Value *> incValues = {};
        int n = phiNode.getNumIncomingValues();
        for(int i = 0; i < n ; i++){
            incValues.push_back(llvmToVanguard.translateValue(phiNode.getIncomingValue(i)));
        }
        return incValues;
    }

    std::vector<Block *> PHINode::getIncomingBlocks() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::vector<Block *> incBlocks = {};
        int n = phiNode.getNumIncomingValues();
        for(int i = 0; i < n ; i++){
            incBlocks.push_back(llvmToVanguard.translateBlock(phiNode.getIncomingBlock(i)));
        }
        return incBlocks;
    }

    const llvm::PHINode &PHINode::unwrap() const{
        return phiNode;
    }

    void PHINode::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Get element pointer
    GetElementPtrInst::GetElementPtrInst(const llvm::GetElementPtrInst &gepi)
            : InstructionClass<llvm::GetElementPtrInst>(GET_ELEMENT_PTR_INST, gepi), getElementPtrInst(gepi) {}

    InstructionVariable* GetElementPtrInst::getLHS() const{
        auto* instvar = new InstructionVariable(getElementPtrInst);
        return instvar;
    }

    Value *GetElementPtrInst::getPointerOperand() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(getElementPtrInst.getPointerOperand());
    }

    Type *GetElementPtrInst::getPointerOperandType() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(getElementPtrInst.getPointerOperandType());
    }

    const llvm::GetElementPtrInst &GetElementPtrInst::unwrap() const{
        return getElementPtrInst;
    }

    void GetElementPtrInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

    //Freeze Instruction
    FreezeInst::FreezeInst(const llvm::FreezeInst &fi): InstructionClass<llvm::FreezeInst>(FREEZE_INST, fi), freezeInst(fi) {}

    Value *FreezeInst::getUnaryOperand() const{
        LLVMtoVanguard &llvMtoVanguard = LLVMtoVanguard::getInstance();
        return llvMtoVanguard.translateValue(freezeInst.getOperand(0));
    }

    const llvm::FreezeInst &FreezeInst::unwrap() const{
        return freezeInst;
    }

    InstructionVariable* FreezeInst::getLHS() const{
        auto* instvar = new InstructionVariable(freezeInst);
        return instvar;
    }

    void FreezeInst::accept(InstructionClassVisitor &v) const {
        return v.visit(*this);
    }

}