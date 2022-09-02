#include "WrappedInstructions.h"
#include "LLVMFactory.h"

namespace vanguard{

    template<>
    std::list<Universe::Instruction*> WrappedInstructionClass<Error, llvm::UnreachableInst>::getAllSuccessors() const {
        return {};
    };

    template<>
    std::list<Universe::Instruction*> WrappedInstructionClass<Return, llvm::ReturnInst>::getAllSuccessors() const {
        return {};
    };

    // Binary Operator
    BinaryIns::BinaryIns(UnitFactory &factory, const llvm::BinaryOperator &bop) : WrappedInstructionClass<BinaryOpExpr, llvm::BinaryOperator>(factory, bop) {}

    BinOp BinaryIns::op() const {
        unsigned opcode = ins.getOpcode();
        BinOp binaryOpClass;
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
            throw std::runtime_error("The opcode "+ std::string(ins.getOpcodeName()) + " is not a binary operator class in vanguard.");
        }
        return binaryOpClass;
    }

    Value* BinaryIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }


    //Compare Instruction
    CmpIns::CmpIns(UnitFactory &factory, const llvm::CmpInst &cmpinst) : WrappedInstructionClass<BinaryOpExpr, llvm::CmpInst>(factory, cmpinst) {}

    BinOp CmpIns::op() const{
        unsigned opcode = ins.getOpcode();
        BinOp binaryOpClass;
        if (opcode == 53 || opcode == 54) binaryOpClass = IFCmpInst;
        else {
            throw std::runtime_error("The opcode "+ std::string(ins.getOpcodeName()) + " is not a cmp operator class in vanguard.");
        }
        return  binaryOpClass;
    }

    Value* CmpIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    //Branch Inst
    BranchIns::BranchIns(UnitFactory &factory, const llvm::BranchInst &brInst) : WrappedInstructionClass<Branch, llvm::BranchInst>(factory, brInst) {}

    bool BranchIns::isConditional() const{
        return ins.isConditional();
    }

    Value* BranchIns::condition() const{
        return factory.createVal(ins.getCondition());
    }

    std::list<Universe::Block*> BranchIns::targets() const{
        std::list<Universe::Block*> successors = {};
        unsigned int n = ins.getNumSuccessors();
        for(unsigned int i = 0; i < n; i++){
            successors.push_back(factory.createBlk(ins.getSuccessor(i)));
        }
        return successors;
    }

    //Indirect Branch Instruction
    IndirectBrIns::IndirectBrIns(UnitFactory &factory, const llvm::IndirectBrInst &ibrInst) : WrappedInstructionClass<Branch, llvm::IndirectBrInst>(factory, ibrInst) {}

    bool IndirectBrIns::isConditional() const {
        return false;
    }

    Value* IndirectBrIns::condition() const{
        throw std::runtime_error("Indirect Branch Instruction does not have a condition.");
    }

    std::list<Universe::Block*> IndirectBrIns::targets() const{
        std::list<Universe::Block*> successors = {};
        unsigned int n = ins.getNumSuccessors();
        for(unsigned int i = 0; i < n; i++){
            successors.push_back(factory.createBlk(ins.getSuccessor(i)));
        }
        return successors;
    }

    //Switch Instruction
    SwitchIns::SwitchIns(UnitFactory &factory, const llvm::SwitchInst &swInst) : WrappedInstructionClass<Branch, llvm::SwitchInst>(factory, swInst) {}

    bool SwitchIns::isConditional() const {
        return true;
    }

    Value* SwitchIns::condition() const{
        return factory.createVal(ins.getCondition());
    }

    std::list<Universe::Block*> SwitchIns::targets() const{
        std::list<Universe::Block*> successors = {};
        unsigned int n = ins.getNumSuccessors();
        for(unsigned int i = 0; i < n; i++){
            successors.push_back(factory.createBlk(ins.getSuccessor(i)));
        }
        return successors;
    }

    //Unary Operator
    UnaryIns::UnaryIns(UnitFactory &factory, const llvm::UnaryOperator &uop) : WrappedInstructionClass<UnaryOpExpr, llvm::UnaryOperator>(factory, uop) {}

    Value* UnaryIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    UnOp UnaryIns::op() const{
        unsigned opcode = ins.getOpcode();
        UnOp unaryOpClass;
        if (opcode == 12) unaryOpClass = Neg;
        else{
            throw std::runtime_error("The opcode "+ std::string(ins.getOpcodeName())+ " is not a unary operator class in Vanguard.");
        }
        return unaryOpClass;
    }

    Value* UnaryIns::operand() const{
        return factory.createVal(ins.getOperand(0));
    }

    //Cast Instruction
    CastIns::CastIns(UnitFactory &factory, const llvm::CastInst &ci): WrappedInstructionClass<CastExpr, llvm::CastInst>(factory, ci) {}

    Value* CastIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    Type *CastIns::castTo() const {
        return factory.createType(ins.getDestTy());
    }

    //Call
    CallIns::CallIns(UnitFactory &factory, const llvm::CallBase &cb) : WrappedInstructionClass<CallExpr, llvm::CallBase>(factory, cb) {}

    Value* CallIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    bool CallIns::hasReturn() const {
        return !ins.doesNotReturn();
    }

    Universe::Function* CallIns::target() const{
        return factory.createFn(ins.getCalledFunction());
    }

    std::list<Value*> CallIns::args() const{
        std::list<Value*> args = {};
        for(auto itr = ins.arg_begin(); itr != ins.arg_end(); itr++){
            args.push_back(factory.createVal(*itr));
        }
        return args;
    }

    //Unreachable Instruction
    UnreachableIns::UnreachableIns(UnitFactory &factory, const llvm::UnreachableInst &ui)
            : WrappedInstructionClass<Error, llvm::UnreachableInst>(factory, ui) {}

    std::string UnreachableIns::msg() const{
        return "This instruction is unreachable.";
    }

    //Return Inst
    ReturnIns::ReturnIns(UnitFactory &factory, const llvm::ReturnInst &retInst) : WrappedInstructionClass<Return, llvm::ReturnInst>(factory, retInst) {}

    bool ReturnIns::returnsValue() const{
        return ins.getReturnValue() != nullptr;
    }

    Value* ReturnIns::value() const{
        return factory.createVal(ins.getReturnValue());
    }

    //Select Inst
    SelectIns::SelectIns(UnitFactory &factory, const llvm::SelectInst &si) : WrappedInstructionClass<TernaryExpr, llvm::SelectInst>(factory, si) {}

    Value* SelectIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    Value *SelectIns::condition() const{
        return factory.createVal(ins.getCondition());
    }

    Value *SelectIns::trueValue() const {
        return factory.createVal(ins.getTrueValue());
    }

    Value *SelectIns::falseValue() const {
        return factory.createVal(ins.getFalseValue());
    }

    //Extract Element Inst
    ExtractElementIns::ExtractElementIns(UnitFactory &factory, const llvm::ExtractElementInst &eei)
            : WrappedInstructionClass<UnknownExpr, llvm::ExtractElementInst>(factory, eei) {}

    Value* ExtractElementIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    /*Value *ExtractElementIns::getVectorOperand() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getVectorOperand());
    }

    Value *ExtractElementIns::getIndexOperand() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getIndexOperand());
    }*/

    //Extract Value Inst
    ExtractValueIns::ExtractValueIns(UnitFactory &factory, const llvm::ExtractValueInst &evi)
            : WrappedInstructionClass<UnknownExpr, llvm::ExtractValueInst>(factory, evi) {}

    Value* ExtractValueIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    /*Value *ExtractValueIns::getAggregateOperand() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getAggregateOperand());
    }

    std::list<unsigned> ExtractValueIns::getIndices() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<unsigned> idxs = {};
        for (unsigned i: ins.indices()){
            idxs.push_back(i);
        }
        return idxs;
    }*/

    //Load Instruction
    LoadIns::LoadIns(UnitFactory &factory, const llvm::LoadInst &li): WrappedInstructionClass<UnknownExpr, llvm::LoadInst>(factory, li) {}

    Value* LoadIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    /*Value *LoadIns::getPointerOperand() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getPointerOperand());
    }

    Type *LoadIns::getPointerOperandType() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(ins.getPointerOperandType());
    }

    unsigned LoadIns::getSize() const{
        return ins.getPointerAddressSpace();
    }*/

    //Insert Value Inst
    InsertValueIns::InsertValueIns(UnitFactory &factory, const llvm::InsertValueInst &ivi)
            : WrappedInstructionClass<UnknownExpr, llvm::InsertValueInst>(factory, ivi) {}

    Value* InsertValueIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    /*Value *InsertValueIns::getAggregateOperand() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getAggregateOperand());
    }

    Value *InsertValueIns::getInsertedValueOperand() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getInsertedValueOperand());
    }

    std::list<unsigned> InsertValueIns::getIndices() const {
        std::list<unsigned> idxs = {};
        for(unsigned i: ins.indices()){
            idxs.push_back(i);
        }
        return idxs;
    }

    MemoryRegion* InsertValueIns::getMemoryAddress() const{
        auto* memAd = new MemoryRegion(ins.getOperand(0), ins.operand(2), sizeof(ins.operand(1)->getType()));
        return memAd;
    }*/

    //Insert Element Inst
    InsertElementIns::InsertElementIns(UnitFactory &factory, const llvm::InsertElementInst &iei)
            : WrappedInstructionClass<UnknownExpr, llvm::InsertElementInst>(factory, iei) {}

    Value* InsertElementIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    /*Value *InsertElementIns::getVector() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getOperand(0));
    }

    Value *InsertElementIns::getInsertedElement() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getOperand(1));
    }

    Value *InsertElementIns::getIndex() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getOperand(2));
    }

    MemoryRegion* InsertElementIns::getMemoryAddress() const{
        auto* memAd = new MemoryRegion(ins.getOperand(0), ins.operand(2), sizeof(ins.operand(1)->getType()));
        return memAd;
    }*/

    //Store Inst
    StoreIns::StoreIns(UnitFactory &factory, const llvm::StoreInst &si) : WrappedInstructionClass<UnknownExpr, llvm::StoreInst>(factory, si) {}

    Value* StoreIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    /*Value *StoreIns::getPointerOperand() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getPointerOperand());
    }

    Value *StoreIns::getValueOperand() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getValueOperand());
    }

    Type *StoreIns::getPointerOperandType() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(ins.getPointerOperandType());
    }

    unsigned StoreIns::getSize() const {
        return ins.getPointerAddressSpace();
    }

    MemoryRegion* StoreIns::getMemoryAddress() const{
        auto* memAd = new MemoryRegion(ins.getPointerOperand(), sizeof(ins.getValueOperand()->getType()));
        return memAd;
    }*/

    //Shuffule Vector Inst
    ShuffleVectorIns::ShuffleVectorIns(UnitFactory &factory, const llvm::ShuffleVectorInst &svi)
            : WrappedInstructionClass<UnknownExpr, llvm::ShuffleVectorInst>(factory, svi) {}

    /*MemoryRegion* ShuffleVectorIns::getMemoryAddress() const{
        auto* memAd = new MemoryRegion(ins.operand(2), sizeof(ins.operand(2)));
        return memAd;
    }*/

    Value* ShuffleVectorIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    //Alloca Instruction
    AllocaIns::AllocaIns(UnitFactory &factory, const llvm::AllocaInst &ai): WrappedInstructionClass<UnknownExpr, llvm::AllocaInst>(factory, ai) {}

    /*Type *AllocaIns::getAllocatedType() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(ins.getAllocatedType());
    }

    MemoryRegion* AllocaIns::getMemoryAddress() const{
        auto* memAd = new MemoryRegion(ins.operand(0), sizeof(ins.operand(0)));
        return memAd;
    }*/

    Value* AllocaIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    //PHI Node
    PHIIns::PHIIns(UnitFactory &factory, const llvm::PHINode &phin) : WrappedInstructionClass<UnknownExpr, llvm::PHINode>(factory, phin) {}

    Value* PHIIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    /*unsigned PHIIns::getNumIncomingValues() const{
        return ins.getNumIncomingValues();
    }

    std::vector<Value *> PHIIns::getIncomingValues() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::vector<Value *> incValues = {};
        int n = ins.getNumIncomingValues();
        for(int i = 0; i < n ; i++){
            incValues.push_back(llvmToVanguard.translateValue(ins.getIncomingValue(i)));
        }
        return incValues;
    }

    std::vector<Block *> PHIIns::getIncomingBlocks() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        std::vector<Block *> incBlocks = {};
        int n = ins.getNumIncomingValues();
        for(int i = 0; i < n ; i++){
            incBlocks.push_back(llvmToVanguard.translateBlock(ins.getIncomingBlock(i)));
        }
        return incBlocks;
    }*/

    //Get element pointer
    GetElementPtrIns::GetElementPtrIns(UnitFactory &factory, const llvm::GetElementPtrInst &gepi)
            : WrappedInstructionClass<UnknownExpr, llvm::GetElementPtrInst>(factory, gepi) {}

    Value* GetElementPtrIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }

    /*Value *GetElementPtrIns::getPointerOperand() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getPointerOperand());
    }

    Type *GetElementPtrIns::getPointerOperandType() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(ins.getPointerOperandType());
    }*/

    //Freeze Instruction
    FreezeIns::FreezeIns(UnitFactory &factory, const llvm::FreezeInst &fi): WrappedInstructionClass<UnknownExpr, llvm::FreezeInst>(factory, fi) {}

    Value* FreezeIns::result() const{
        auto* insVar = factory.createVal(&ins);
        return insVar;
    }
}