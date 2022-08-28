#include "WrappedInstructions.h"
#include "LLVMtoVanguard.h"

namespace vanguard{

    template<>
    std::list<Instruction*> WrappedInstructionClass<Error, llvm::UnreachableInst>::getAllSuccessors() const {
        return {};
    };

    template<>
    std::list<Instruction*> WrappedInstructionClass<Return, llvm::ReturnInst>::getAllSuccessors() const {
        return {};
    };

    // Binary Operator
    BinaryIns::BinaryIns(const llvm::BinaryOperator &bop) : WrappedInstructionClass<BinaryOpExpr, llvm::BinaryOperator>(bop) {}

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

    Variable* BinaryIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
        return insVar;
    }


    //Compare Instruction
    CmpIns::CmpIns(const llvm::CmpInst &cmpinst) : WrappedInstructionClass<BinaryOpExpr, llvm::CmpInst>(cmpinst) {}

    BinOp CmpIns::op() const{
        unsigned opcode = ins.getOpcode();
        BinOp binaryOpClass;
        if (opcode == 53 || opcode == 54) binaryOpClass = IFCmpInst;
        else {
            throw std::runtime_error("The opcode "+ std::string(ins.getOpcodeName()) + " is not a cmp operator class in vanguard.");
        }
        return  binaryOpClass;
    }

    Variable* CmpIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
        return insVar;
    }

    //Branch Inst
    BranchIns::BranchIns(const llvm::BranchInst &brInst) : WrappedInstructionClass<Branch, llvm::BranchInst>(brInst) {}

    bool BranchIns::isConditional() const{
        return ins.isConditional();
    }

    Value* BranchIns::condition() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getCondition());
    }

    std::list<Block*> BranchIns::targets() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Block*> successors = {};
        unsigned int n = ins.getNumSuccessors();
        for(unsigned int i = 0; i < n; i++){
            successors.push_back(llvmToVanguard.translateBlock(ins.getSuccessor(i)));
        }
        return successors;
    }

    //Indirect Branch Instruction
    IndirectBrIns::IndirectBrIns(const llvm::IndirectBrInst &ibrInst) : WrappedInstructionClass<Branch, llvm::IndirectBrInst>(ibrInst) {}

    bool IndirectBrIns::isConditional() const {
        return false;
    }

    Value* IndirectBrIns::condition() const{
        throw std::runtime_error("Indirect Branch Instruction does not have a condition.");
    }

    std::list<Block*> IndirectBrIns::targets() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Block*> successors = {};
        unsigned int n = ins.getNumSuccessors();
        for(unsigned int i = 0; i < n; i++){
            successors.push_back(llvmToVanguard.translateBlock(ins.getSuccessor(i)));
        }
        return successors;
    }

    //Switch Instruction
    SwitchIns::SwitchIns(const llvm::SwitchInst &swInst) : WrappedInstructionClass<Branch, llvm::SwitchInst>(swInst) {}

    bool SwitchIns::isConditional() const {
        return true;
    }

    Value* SwitchIns::condition() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getCondition());
    }

    std::list<Block*> SwitchIns::targets() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Block*> successors = {};
        unsigned int n = ins.getNumSuccessors();
        for(unsigned int i = 0; i < n; i++){
            successors.push_back(llvmToVanguard.translateBlock(ins.getSuccessor(i)));
        }
        return successors;
    }

    //Unary Operator
    UnaryIns::UnaryIns(const llvm::UnaryOperator &uop) : WrappedInstructionClass<UnaryOpExpr, llvm::UnaryOperator>(uop) {}

    Variable* UnaryIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
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
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getOperand(0));
    }

    //Cast Instruction
    CastIns::CastIns(const llvm::CastInst &ci): WrappedInstructionClass<CastExpr, llvm::CastInst>(ci) {}

    Variable* CastIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
        return insVar;
    }

    Type *CastIns::castTo() const {
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(ins.getDestTy());
    }

    //Call
    CallIns::CallIns(const llvm::CallBase &cb) : WrappedInstructionClass<CallExpr, llvm::CallBase>(cb) {}

    Variable* CallIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
        return insVar;
    }

    bool CallIns::hasReturn() const {
        return !ins.doesNotReturn();
    }

    Function* CallIns::getTarget() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateFunction(ins.getFunction());
    }

    std::list<Value*> CallIns::getArgs() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        std::list<Value*> args = {};
        for(auto itr = ins.arg_begin(); itr != ins.arg_end(); itr++){
            args.push_back(llvmToVanguard.translateValue(*itr));
        }
        return args;
    }

    //Unreachable Instruction
    UnreachableIns::UnreachableIns(const llvm::UnreachableInst &ui)
            : WrappedInstructionClass<Error, llvm::UnreachableInst>(ui) {}

    std::string UnreachableIns::msg() const{
        return "This instruction is unreachable.";
    }

    //Return Inst
    ReturnIns::ReturnIns(const llvm::ReturnInst &retInst) : WrappedInstructionClass<Return, llvm::ReturnInst>(retInst) {}

    bool ReturnIns::returnsValue() const{
        return ins.getReturnValue() != nullptr;
    }

    Value* ReturnIns::value() const{
        LLVMtoVanguard& llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getReturnValue());
    }

    //Select Inst
    SelectIns::SelectIns(const llvm::SelectInst &si) : WrappedInstructionClass<TernaryExpr, llvm::SelectInst>(si) {}

    Variable* SelectIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
        return insVar;
    }

    Value *SelectIns::condition() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getCondition());
    }

    Value *SelectIns::trueValue() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getTrueValue());
    }

    Value *SelectIns::falseValue() const {
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateValue(ins.getFalseValue());
    }

    //Extract Element Inst
    ExtractElementIns::ExtractElementIns(const llvm::ExtractElementInst &eei)
            : WrappedInstructionClass<UnknownExpr, llvm::ExtractElementInst>(eei) {}

    Variable* ExtractElementIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
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
    ExtractValueIns::ExtractValueIns(const llvm::ExtractValueInst &evi)
            : WrappedInstructionClass<UnknownExpr, llvm::ExtractValueInst>(evi) {}

    Variable* ExtractValueIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
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
    LoadIns::LoadIns(const llvm::LoadInst &li): WrappedInstructionClass<UnknownExpr, llvm::LoadInst>(li) {}

    Variable* LoadIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
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
    InsertValueIns::InsertValueIns(const llvm::InsertValueInst &ivi)
            : WrappedInstructionClass<UnknownExpr, llvm::InsertValueInst>(ivi) {}

    Variable* InsertValueIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
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
    InsertElementIns::InsertElementIns(const llvm::InsertElementInst &iei)
            : WrappedInstructionClass<UnknownExpr, llvm::InsertElementInst>(iei) {}

    Variable* InsertElementIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
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
    StoreIns::StoreIns(const llvm::StoreInst &si) : WrappedInstructionClass<UnknownExpr, llvm::StoreInst>(si) {}

    Variable* StoreIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
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
    ShuffleVectorIns::ShuffleVectorIns(const llvm::ShuffleVectorInst &svi)
            : WrappedInstructionClass<UnknownExpr, llvm::ShuffleVectorInst>(svi) {}

    /*MemoryRegion* ShuffleVectorIns::getMemoryAddress() const{
        auto* memAd = new MemoryRegion(ins.operand(2), sizeof(ins.operand(2)));
        return memAd;
    }*/

    Variable* ShuffleVectorIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
        return insVar;
    }

    //Alloca Instruction
    AllocaIns::AllocaIns(const llvm::AllocaInst &ai): WrappedInstructionClass<UnknownExpr, llvm::AllocaInst>(ai) {}

    /*Type *AllocaIns::getAllocatedType() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        return llvmToVanguard.translateType(ins.getAllocatedType());
    }

    MemoryRegion* AllocaIns::getMemoryAddress() const{
        auto* memAd = new MemoryRegion(ins.operand(0), sizeof(ins.operand(0)));
        return memAd;
    }*/

    Variable* AllocaIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
        return insVar;
    }

    //PHI Node
    PHIIns::PHIIns(const llvm::PHINode &phin) : WrappedInstructionClass<UnknownExpr, llvm::PHINode>(phin) {}

    Variable* PHIIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
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
    GetElementPtrIns::GetElementPtrIns(const llvm::GetElementPtrInst &gepi)
            : WrappedInstructionClass<UnknownExpr, llvm::GetElementPtrInst>(gepi) {}

    Variable* GetElementPtrIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
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
    FreezeIns::FreezeIns(const llvm::FreezeInst &fi): WrappedInstructionClass<UnknownExpr, llvm::FreezeInst>(fi) {}

    Variable* FreezeIns::result() const{
        LLVMtoVanguard &llvmToVanguard = LLVMtoVanguard::getInstance();
        auto* insVar = llvmToVanguard.translateInsVar(&ins);
        return insVar;
    }
}