#include "LLVMtoVanguard.h"
#include "Function.h"
#include "Block.h"
#include "Instruction.h"
#include "WrappedInstructions.h"
#include "CompilationUnit.h"
#include "Type.h"
#include "Value.h"

namespace vanguard{
    
    LLVMtoVanguard* LLVMtoVanguard::singletonLLVMtoVanguard = nullptr;

    LLVMtoVanguard::LLVMtoVanguard(){
    }

    LLVMtoVanguard& LLVMtoVanguard::getInstance(){
        if (singletonLLVMtoVanguard == nullptr){
            singletonLLVMtoVanguard = new LLVMtoVanguard();
        }
        return *singletonLLVMtoVanguard;
    }

    CompilationUnit* LLVMtoVanguard::translateModule(const llvm::Module* module) {
        if(module == nullptr) {
            return nullptr;
        }

        if(moduleMap.find(module) == moduleMap.end()){
            moduleMap[module] = new CompilationUnit(*module);
        }
        return moduleMap[module];
    }

    Function* LLVMtoVanguard::translateFunction(const llvm::Function* fn) {
        if(fn == nullptr) {
            return nullptr;
        }

        if(functionMap.find(fn) == functionMap.end()) {
            functionMap[fn] = new Function(*fn);
        }
        return functionMap[fn];
    }

    Instruction* LLVMtoVanguard::translateInstruction(const llvm::Instruction* ins) {
        if(ins == nullptr) {
            return nullptr;
        }

        if (instructionMap.find(ins) == instructionMap.end()) {
            unsigned opcode = ins->getOpcode();
            if (opcode == 1) instructionMap[ins] = new ReturnIns(*llvm::dyn_cast<llvm::ReturnInst>(ins));
            else if (opcode == 2) instructionMap[ins] = new BranchIns(*llvm::dyn_cast<llvm::BranchInst>(ins));
            else if (opcode == 3)  instructionMap[ins] = new SwitchIns(*llvm::dyn_cast<llvm::SwitchInst>(ins));
            else if (opcode == 4) instructionMap[ins] = new IndirectBrIns(*llvm::dyn_cast<llvm::IndirectBrInst>(ins));
            else if (opcode == 7) instructionMap[ins] = new UnreachableIns(*llvm::dyn_cast<llvm::UnreachableInst>(ins));
            else if (opcode == 12) instructionMap[ins] = new UnaryIns(*llvm::dyn_cast<llvm::UnaryOperator>(ins));
            else if (opcode >= 13 && opcode <= 30) instructionMap[ins] = new BinaryIns(*llvm::dyn_cast<llvm::BinaryOperator>(ins));
            else if (opcode == 31) instructionMap[ins] = new AllocaIns(*llvm::dyn_cast<llvm::AllocaInst>(ins));
            else if (opcode == 32) instructionMap[ins] = new LoadIns(*llvm::dyn_cast<llvm::LoadInst>(ins));
            else if (opcode == 33)  instructionMap[ins] = new StoreIns(*llvm::dyn_cast<llvm::StoreInst>(ins));
            else if (opcode == 34) instructionMap[ins] = new GetElementPtrIns(*llvm::dyn_cast<llvm::GetElementPtrInst>(ins));
            else if (opcode >= 38 && opcode <= 50) instructionMap[ins] = new CastIns(*llvm::dyn_cast<llvm::CastInst>(ins));
            else if (opcode == 53 || opcode == 54) instructionMap[ins] = new CmpIns(*llvm::dyn_cast<llvm::CmpInst>(ins));
            else if (opcode == 55) instructionMap[ins] = new PHIIns(*llvm::dyn_cast<llvm::PHINode>(ins));
            else if (opcode == 56) instructionMap[ins] = new CallIns(*llvm::dyn_cast<llvm::CallBase>(ins));
            else if (opcode == 57) instructionMap[ins] = new SelectIns(*llvm::dyn_cast<llvm::SelectInst>(ins));
            else if (opcode == 61) instructionMap[ins] = new ExtractElementIns(*llvm::dyn_cast<llvm::ExtractElementInst>(ins));
            else if (opcode == 62) instructionMap[ins] = new InsertElementIns(*llvm::dyn_cast<llvm::InsertElementInst>(ins));
            else if (opcode == 63) instructionMap[ins] = new ShuffleVectorIns(*llvm::dyn_cast<llvm::ShuffleVectorInst>(ins));
            else if (opcode == 64) instructionMap[ins] = new ExtractValueIns(*llvm::dyn_cast<llvm::ExtractValueInst>(ins));
            else if (opcode == 65) instructionMap[ins] = new InsertValueIns(*llvm::dyn_cast<llvm::InsertValueInst>(ins));
            else if (opcode == 67) instructionMap[ins] = new FreezeIns(*llvm::dyn_cast<llvm::FreezeInst>(ins));
            else throw std::runtime_error("The instruction class " + (std::string)ins->getOpcodeName() + " with opcode " + std::to_string(opcode) + " does not exist in Vanguard yet.");
        }
        return instructionMap[ins];
    }

    Block* LLVMtoVanguard::translateBlock(const llvm::BasicBlock* block){
        if(block == nullptr) {
            return nullptr;
        }

        if (blockMap.find(block) == blockMap.end()){
            blockMap[block] = new Block(*block);
        }
        return blockMap[block];
    }

    Type* LLVMtoVanguard::translateType(const llvm::Type* t){
        if(t == nullptr) {
            return nullptr;
        }

        if (typeMap.find(t) == typeMap.end()){
            if (auto integer = llvm::dyn_cast<llvm::IntegerType>(t)){
                typeMap[t] = (new IntegerType(*integer));
            }
            else if (auto array = llvm::dyn_cast<llvm::ArrayType>(t)){
                typeMap[t] = new ArrayType(*array);
            }
//             else if (auto function = llvm::dyn_cast<llvm::FunctionType>(t)){
//                 typeMap[t] = new FunctionT(*function);
//             }
            else if (auto pointer = llvm::dyn_cast<llvm::PointerType>(t)){
                typeMap[t] = new PointerType(*pointer);
            }
            else if (auto structT = llvm::dyn_cast<llvm::StructType>(t)){
                typeMap[t] = new StructType(*structT);
            }
            else if (auto vector = llvm::dyn_cast<llvm::VectorType>(t)){
                typeMap[t] = new VectorType(*vector);
            }
            else if (t->isVoidTy()){
                typeMap[t] = new VoidType(*t);
            }
            else if (t->isLabelTy()){
                typeMap[t] = new LabelType(*t);
            }
            else {
                throw std::runtime_error("Given type cannot be translated since it does not exist in vanguard yet.");
            }
        }
        return typeMap[t];
    }

    Value* LLVMtoVanguard::translateValue(const llvm::Value* val){
        if(val == nullptr) {
            return nullptr;
        }

        if (valueMap.find(val) == valueMap.end()){
            if (auto globalVariable = llvm::dyn_cast<llvm::GlobalVariable>(val)){
                valueMap[val] = new GlobalVariable(*globalVariable);
            }
            else if (auto argument = llvm::dyn_cast<llvm::Argument>(val)){
                valueMap[val] = new Argument(*argument);
            }
            else if (auto instVar = llvm::dyn_cast<llvm::Instruction>(val)){
                valueMap[val] = new InstructionVariable(*instVar);
            }
            else if (auto integer = llvm::dyn_cast<llvm::ConstantInt>(val)){
                valueMap[val] = new IntegerLiteral(*integer);
            }
            else if (auto string = llvm::dyn_cast<llvm::ConstantDataSequential>(val)){
                valueMap[val] = new StringLiteral(*string);
            }
            else if(auto constant = llvm::dyn_cast<llvm::Constant>(val)){
                valueMap[val] = new Constant(*constant);
            }
            else if(auto loc = llvm::dyn_cast<llvm::BasicBlock>(val)) {
                valueMap[val] = new Location(*loc);
            }
            else{
                throw std::runtime_error("Given value cannot be translated since it does not exist in vanguard yet.");
            }
        }
        return valueMap[val];
    }

    InstructionVariable *LLVMtoVanguard::translateInsVar(const llvm::Instruction *ins) {
        if(ins == nullptr) {
            return nullptr;
        }

        if (valueMap.find(ins) == valueMap.end()) {
            valueMap[ins] = new InstructionVariable(*ins);
        }

        return llvm::dyn_cast<InstructionVariable>(valueMap[ins]);
    }
}