//
// Created by Jon Stephens on 9/1/22.
//

#include "BlockchainFactory.h"
#include <program/Universe.h>
#include <program/CompilationUnit.h>
#include <program/WrappedInstructions.h>
#include "Blockchain.h"

namespace vanguard {
    Universe::CompilationUnit *BlockchainFactory::createUnit(const llvm::Module *module) {
        if(module == nullptr) {
            return nullptr;
        }

        if(moduleMap.find(module) == moduleMap.end()){
            moduleMap[module] = new Blockchain<Universe>::CompilationUnit(*this, *module);
        }
        return moduleMap[module];
    }

    Universe::Function *BlockchainFactory::createFn(const llvm::Function *fn) {
        if(fn == nullptr) {
            return nullptr;
        }

        if(functionMap.find(fn) == functionMap.end()) {
            functionMap[fn] = new Blockchain<Universe>::Function(*this, *fn);
        }
        return functionMap[fn];
    }

    Universe::Instruction *BlockchainFactory::createIns(const llvm::Instruction *ins)  {
        if(ins == nullptr) {
            return nullptr;
        }

        if (instructionMap.find(ins) == instructionMap.end()) {
            unsigned opcode = ins->getOpcode();
            if (opcode == 1) instructionMap[ins] = new ReturnIns(*this,*llvm::dyn_cast<llvm::ReturnInst>(ins));
            else if (opcode == 2) instructionMap[ins] = new BranchIns(*this,*llvm::dyn_cast<llvm::BranchInst>(ins));
            else if (opcode == 3)  instructionMap[ins] = new SwitchIns(*this,*llvm::dyn_cast<llvm::SwitchInst>(ins));
            else if (opcode == 4) instructionMap[ins] = new IndirectBrIns(*this,*llvm::dyn_cast<llvm::IndirectBrInst>(ins));
            else if (opcode == 7) instructionMap[ins] = new UnreachableIns(*this,*llvm::dyn_cast<llvm::UnreachableInst>(ins));
            else if (opcode == 12) instructionMap[ins] = new UnaryIns(*this,*llvm::dyn_cast<llvm::UnaryOperator>(ins));
            else if (opcode >= 13 && opcode <= 30) instructionMap[ins] = new BinaryIns(*this,*llvm::dyn_cast<llvm::BinaryOperator>(ins));
            else if (opcode == 31) instructionMap[ins] = new AllocaIns(*this,*llvm::dyn_cast<llvm::AllocaInst>(ins));
            else if (opcode == 32) instructionMap[ins] = new LoadIns(*this,*llvm::dyn_cast<llvm::LoadInst>(ins));
            else if (opcode == 33)  instructionMap[ins] = new StoreIns(*this,*llvm::dyn_cast<llvm::StoreInst>(ins));
            else if (opcode == 34) instructionMap[ins] = new GetElementPtrIns(*this,*llvm::dyn_cast<llvm::GetElementPtrInst>(ins));
            else if (opcode >= 38 && opcode <= 50) instructionMap[ins] = new CastIns(*this,*llvm::dyn_cast<llvm::CastInst>(ins));
            else if (opcode == 53 || opcode == 54) instructionMap[ins] = new CmpIns(*this,*llvm::dyn_cast<llvm::CmpInst>(ins));
            else if (opcode == 55) instructionMap[ins] = new PHIIns(*this,*llvm::dyn_cast<llvm::PHINode>(ins));
            else if (opcode == 56) instructionMap[ins] = new CallIns(*this,*llvm::dyn_cast<llvm::CallBase>(ins));
            else if (opcode == 57) instructionMap[ins] = new SelectIns(*this,*llvm::dyn_cast<llvm::SelectInst>(ins));
            else if (opcode == 61) instructionMap[ins] = new ExtractElementIns(*this,*llvm::dyn_cast<llvm::ExtractElementInst>(ins));
            else if (opcode == 62) instructionMap[ins] = new InsertElementIns(*this,*llvm::dyn_cast<llvm::InsertElementInst>(ins));
            else if (opcode == 63) instructionMap[ins] = new ShuffleVectorIns(*this,*llvm::dyn_cast<llvm::ShuffleVectorInst>(ins));
            else if (opcode == 64) instructionMap[ins] = new ExtractValueIns(*this,*llvm::dyn_cast<llvm::ExtractValueInst>(ins));
            else if (opcode == 65) instructionMap[ins] = new InsertValueIns(*this,*llvm::dyn_cast<llvm::InsertValueInst>(ins));
            else if (opcode == 67) instructionMap[ins] = new FreezeIns(*this,*llvm::dyn_cast<llvm::FreezeInst>(ins));
            else throw std::runtime_error("The instruction class " + (std::string)ins->getOpcodeName() + " with opcode " + std::to_string(opcode) + " does not exist in Vanguard yet.");
        }
        return instructionMap[ins];
    }

    Universe::Block *BlockchainFactory::createBlk(const llvm::BasicBlock *block) {
        if(block == nullptr) {
            return nullptr;
        }

        if (blockMap.find(block) == blockMap.end()){
            blockMap[block] = new Blockchain<Universe>::Block(*this,*block);
        }
        return blockMap[block];
    }

    Type *BlockchainFactory::createType(const llvm::Type *t) {
        if(t == nullptr) {
            return nullptr;
        }

        if (typeMap.find(t) == typeMap.end()){
            if (auto integer = llvm::dyn_cast<llvm::IntegerType>(t)){
                typeMap[t] = (new IntegerType(*this,*integer));
            }
            else if (auto array = llvm::dyn_cast<llvm::ArrayType>(t)){
                typeMap[t] = new ArrayType(*this,*array);
            }
                // else if (auto function = llvm::dyn_cast<llvm::FunctionType>(&t)){
                //     typeMap[&t] = new FunctionT(*function);
                // }
            else if (auto pointer = llvm::dyn_cast<llvm::PointerType>(t)){
                typeMap[t] = new PointerType(*this,*pointer);
            }
            else if (auto structT = llvm::dyn_cast<llvm::StructType>(t)){
                typeMap[t] = new StructType(*this,*structT);
            }
            else if (auto vector = llvm::dyn_cast<llvm::VectorType>(t)){
                typeMap[t] = new VectorType(*this,*vector);
            }
            else if (t->isVoidTy()){
                typeMap[t] = new VoidType(*this,*t);
            }
            else if (t->isLabelTy()){
                typeMap[t] = new LabelType(*this,*t);
            }
            else {
                throw std::runtime_error("Given type cannot be translated since it does not exist in vanguard yet.");
            }
        }
        return typeMap[t];
    }

    Value *BlockchainFactory::createVal(const llvm::Value *val) {
        if(val == nullptr) {
            return nullptr;
        }

        if (valueMap.find(val) == valueMap.end()){
            if (auto globalVariable = llvm::dyn_cast<llvm::GlobalVariable>(val)){
                valueMap[val] = new GlobalVariable(*this,*globalVariable);
            }
            else if (auto argument = llvm::dyn_cast<llvm::Argument>(val)){
                valueMap[val] = new Argument(*this,*argument);
            }
            else if (auto instVar = llvm::dyn_cast<llvm::Instruction>(val)){
                valueMap[val] = new InstructionVariable(*this,*instVar);
            }
            else if (auto integer = llvm::dyn_cast<llvm::ConstantInt>(val)){
                valueMap[val] = new IntegerLiteral(*this,*integer);
            }
            else if (auto string = llvm::dyn_cast<llvm::ConstantDataSequential>(val)){
                valueMap[val] = new StringLiteral(*this,*string);
            }
            else if(auto constant = llvm::dyn_cast<llvm::Constant>(val)){
                valueMap[val] = new Constant(*this,*constant);
            }
            else if(auto loc = llvm::dyn_cast<llvm::BasicBlock>(val)) {
                valueMap[val] = new Location(*this,*loc);
            }
            else{
                throw std::runtime_error("Given value cannot be translated since it does not exist in vanguard yet.");
            }
        }
        return valueMap[val];
    }
}