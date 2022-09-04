#include "LLVMFactory.h"
#include "WrappedInstructions.h"
#include "Type.h"
#include "Value.h"
#include <program/WrappedValue.h>
#include <program/WrappedType.h>
#include "Top.h"

namespace vanguard{

    LLVMFactory::LLVMFactory() {
    }

    Universe::CompilationUnit *LLVMFactory::createUnit(const llvm::Module *module) {
        if(module == nullptr) {
            return nullptr;
        }

        if(moduleMap.find(module) == moduleMap.end()){
            moduleMap[module] = new Top<Universe>::CompilationUnit(*this, module);
        }
        return moduleMap[module];
    }

    Universe::Function *LLVMFactory::createFn(const llvm::Function *fn) {
        if(fn == nullptr) {
            return nullptr;
        }

        if(functionMap.find(fn) == functionMap.end()) {
            functionMap[fn] = new Top<Universe>::Function(*this, fn);
        }
        return functionMap[fn];
    }

    Universe::Instruction *LLVMFactory::createIns(const llvm::Instruction *ins)  {
        if(ins == nullptr) {
            return nullptr;
        }

        if (instructionMap.find(ins) == instructionMap.end()) {
            unsigned opcode = ins->getOpcode();
            if (opcode == 1) instructionMap[ins] = new ReturnIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::ReturnInst>(ins));
            else if (opcode == 2) instructionMap[ins] = new BranchIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::BranchInst>(ins));
            else if (opcode == 3)  instructionMap[ins] = new SwitchIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::SwitchInst>(ins));
            else if (opcode == 4) instructionMap[ins] = new IndirectBrIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::IndirectBrInst>(ins));
            else if (opcode == 7) instructionMap[ins] = new UnreachableIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::UnreachableInst>(ins));
            else if (opcode == 12) instructionMap[ins] = new UnaryIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::UnaryOperator>(ins));
            else if (opcode >= 13 && opcode <= 30) instructionMap[ins] = new BinaryIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::BinaryOperator>(ins));
            else if (opcode == 31) instructionMap[ins] = new AllocaIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::AllocaInst>(ins));
            else if (opcode == 32) instructionMap[ins] = new LoadIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::LoadInst>(ins));
            else if (opcode == 33)  instructionMap[ins] = new StoreIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::StoreInst>(ins));
            else if (opcode == 34) instructionMap[ins] = new GetElementPtrIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::GetElementPtrInst>(ins));
            else if (opcode >= 38 && opcode <= 50) instructionMap[ins] = new CastIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::CastInst>(ins));
            else if (opcode == 53 || opcode == 54) instructionMap[ins] = new CmpIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::CmpInst>(ins));
            else if (opcode == 55) instructionMap[ins] = new PHIIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::PHINode>(ins));
            else if (opcode == 56) instructionMap[ins] = new CallIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::CallBase>(ins));
            else if (opcode == 57) instructionMap[ins] = new SelectIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::SelectInst>(ins));
            else if (opcode == 61) instructionMap[ins] = new ExtractElementIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::ExtractElementInst>(ins));
            else if (opcode == 62) instructionMap[ins] = new InsertElementIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::InsertElementInst>(ins));
            else if (opcode == 63) instructionMap[ins] = new ShuffleVectorIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::ShuffleVectorInst>(ins));
            else if (opcode == 64) instructionMap[ins] = new ExtractValueIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::ExtractValueInst>(ins));
            else if (opcode == 65) instructionMap[ins] = new InsertValueIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::InsertValueInst>(ins));
            else if (opcode == 67) instructionMap[ins] = new FreezeIns<Top<Universe>>(*this,*llvm::dyn_cast<llvm::FreezeInst>(ins));
            else throw std::runtime_error("The instruction class " + (std::string)ins->getOpcodeName() + " with opcode " + std::to_string(opcode) + " does not exist in Vanguard yet.");
        }
        return instructionMap[ins];
    }

    Universe::Block *LLVMFactory::createBlk(const llvm::BasicBlock *block) {
        if(block == nullptr) {
            return nullptr;
        }

        if (blockMap.find(block) == blockMap.end()){
            blockMap[block] = new Top<Universe>::Block(*this, block);
        }
        return blockMap[block];
    }

    Type *LLVMFactory::createType(const llvm::Type *t) {
        if(t == nullptr) {
            return nullptr;
        }

        if (typeMap.find(t) == typeMap.end()){
            if (auto integer = llvm::dyn_cast<llvm::IntegerType>(t)){
                //typeMap[t] = (new IntegerType(*this,*integer));
                typeMap[t] = new WrappedIntegerType<IntegerType>(*integer, *this);
            }
            else if (auto array = llvm::dyn_cast<llvm::ArrayType>(t)){
                //typeMap[t] = new ArrayType(*this,*array);
                typeMap[t] = new WrappedArrayType<ArrayType, llvm::ArrayType>(*array, *this);
            }
                // else if (auto function = llvm::dyn_cast<llvm::FunctionType>(&t)){
                //     typeMap[&t] = new FunctionT(*function);
                // }
            else if (auto pointer = llvm::dyn_cast<llvm::PointerType>(t)){
                //typeMap[t] = new PointerType(*this,*pointer);
                typeMap[t] = new WrappedPointerType<PointerType, llvm::PointerType>(*pointer, *this);
            }
            else if (auto structT = llvm::dyn_cast<llvm::StructType>(t)){
                typeMap[t] = new WrappedStructType<StructType, llvm::StructType>(*structT, *this);
            }
            else if (auto vector = llvm::dyn_cast<llvm::VectorType>(t)){
                typeMap[t] = new WrappedVectorType<ArrayType>(*vector, *this);
            }
            else if (t->isVoidTy()){
                //typeMap[t] = new VoidType(*this,*t);
                typeMap[t] = new WrappedVoidType<VoidType, llvm::Type>(*t, *this);
            }
            else if (t->isLabelTy()){
                typeMap[t] = new WrappedLocationType<LocationType, llvm::Type>(*t, *this);
            }
            else {
                throw std::runtime_error("Given type cannot be translated since it does not exist in vanguard yet.");
            }
        }
        return typeMap[t];
    }

    Value *LLVMFactory::createVal(const llvm::Value *val) {
        if(val == nullptr) {
            return nullptr;
        }

        if (valueMap.find(val) == valueMap.end()){
            if (auto globalVariable = llvm::dyn_cast<llvm::GlobalVariable>(val)){
                valueMap[val] = new WrappedVariable<Variable, llvm::GlobalVariable>(*globalVariable, *this);
            }
            else if (auto argument = llvm::dyn_cast<llvm::Argument>(val)){
                valueMap[val] = new WrappedVariable<Variable, llvm::Argument>(*argument, *this);
            }
            else if (auto instVar = llvm::dyn_cast<llvm::Instruction>(val)){
                valueMap[val] = new WrappedVariable<Variable, llvm::Instruction>(*instVar, *this);
            }
            else if (auto integer = llvm::dyn_cast<llvm::ConstantInt>(val)){
                valueMap[val] = new WrappedLiteral<Literal, llvm::ConstantInt>(*integer, *this);
            }
            else if (auto string = llvm::dyn_cast<llvm::ConstantDataSequential>(val)){
                valueMap[val] = new WrappedLiteral<Literal, llvm::ConstantDataSequential>(*string, *this);
            }
            else if(auto constant = llvm::dyn_cast<llvm::Constant>(val)){
                valueMap[val] = new WrappedConstant<Constant, llvm::Constant>(*constant, *this);
            }
            else if(auto loc = llvm::dyn_cast<llvm::BasicBlock>(val)) {
                valueMap[val] = new WrappedLocation<Location, llvm::BasicBlock>(*loc, *this);
            }
            else{
                throw std::runtime_error("Given value cannot be translated since it does not exist in vanguard yet.");
            }
        }
        return valueMap[val];
    }
}