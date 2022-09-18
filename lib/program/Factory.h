//
// Created by Jon Stephens on 9/16/22.
//

#ifndef VANGUARD_FACTORY_H
#define VANGUARD_FACTORY_H

#include "Base.h"
#include <unordered_map>
#include <llvm/IR/Instructions.h>

#include "CompilationUnit.h"
#include "Value.h"
#include "Block.h"
#include "Instruction.h"
#include "Function.h"

namespace vanguard {
    template<typename Domain>
    class Base<Domain>::Factory {
    public:
        Factory() = default;

        typename Domain::CompilationUnit *createUnit(const llvm::Module *module) {
            if(module == nullptr) {
                return nullptr;
            }

            if(moduleMap.find(module) == moduleMap.end()){
                moduleMap[module] = new typename Domain::CompilationUnit(*this, module);
            }
            return moduleMap[module];
        }

        typename Domain::Function *createFn(const llvm::Function *fn) {
            if(fn == nullptr) {
                return nullptr;
            }

            if(functionMap.find(fn) == functionMap.end()) {
                functionMap[fn] = new typename Domain::Function(*this, fn);
            }
            return functionMap[fn];
        }

        typename Domain::Instruction *createIns(const llvm::Instruction *ins) {
            if(ins == nullptr) {
                return nullptr;
            }

            if (instructionMap.find(ins) == instructionMap.end()) {
                unsigned opcode = ins->getOpcode();
                if (opcode == 1) instructionMap[ins] = new typename Domain::template ReturnIns<llvm::ReturnInst>(llvm::dyn_cast<llvm::ReturnInst>(ins), *this);
                else if (opcode == 2) instructionMap[ins] = new typename Domain::template BranchIns<llvm::BranchInst>(llvm::dyn_cast<llvm::BranchInst>(ins), *this);
                else if (opcode == 3)  instructionMap[ins] = new typename Domain::template BranchIns<llvm::SwitchInst>(llvm::dyn_cast<llvm::SwitchInst>(ins), *this);
                else if (opcode == 4) instructionMap[ins] = new typename Domain::template BranchIns<llvm::IndirectBrInst>(llvm::dyn_cast<llvm::IndirectBrInst>(ins), *this);
                else if (opcode == 7) instructionMap[ins] = new typename Domain::template ErrorIns<llvm::UnreachableInst>(llvm::dyn_cast<llvm::UnreachableInst>(ins), *this);
                else if (opcode == 12) instructionMap[ins] = new typename Domain::template UnaryOpIns<llvm::UnaryOperator>(llvm::dyn_cast<llvm::UnaryOperator>(ins), *this);
                else if (opcode >= 13 && opcode <= 30) instructionMap[ins] = new typename Domain::template BinaryOpIns<llvm::BinaryOperator>(llvm::dyn_cast<llvm::BinaryOperator>(ins), *this);
                else if (opcode == 31) instructionMap[ins] = new typename Domain::template UnknownIns<llvm::AllocaInst>(llvm::dyn_cast<llvm::AllocaInst>(ins), *this);
                else if (opcode == 32) instructionMap[ins] = new typename Domain::template UnknownIns<llvm::LoadInst>(llvm::dyn_cast<llvm::LoadInst>(ins), *this);
                else if (opcode == 33)  instructionMap[ins] = new typename Domain::template UnknownIns<llvm::StoreInst>(llvm::dyn_cast<llvm::StoreInst>(ins), *this);
                else if (opcode == 34) instructionMap[ins] = new typename Domain::template UnknownIns<llvm::GetElementPtrInst>(llvm::dyn_cast<llvm::GetElementPtrInst>(ins), *this);
                else if (opcode >= 38 && opcode <= 50) instructionMap[ins] = new typename Domain::template CastIns<llvm::CastInst>(llvm::dyn_cast<llvm::CastInst>(ins), *this);
                else if (opcode == 53 || opcode == 54) instructionMap[ins] = new typename Domain::template BinaryOpIns<llvm::CmpInst>(llvm::dyn_cast<llvm::CmpInst>(ins), *this);
                else if (opcode == 55) instructionMap[ins] = new typename Domain::template UnknownIns<llvm::PHINode>(llvm::dyn_cast<llvm::PHINode>(ins), *this);
                else if (opcode == 56) instructionMap[ins] = new typename Domain::template CallIns<llvm::CallBase>(llvm::dyn_cast<llvm::CallBase>(ins), *this);
                else if (opcode == 57) instructionMap[ins] = new typename Domain::template TernaryIns<llvm::SelectInst>(llvm::dyn_cast<llvm::SelectInst>(ins), *this);
                else if (opcode == 61) instructionMap[ins] = new typename Domain::template UnknownIns<llvm::ExtractElementInst>(llvm::dyn_cast<llvm::ExtractElementInst>(ins), *this);
                else if (opcode == 62) instructionMap[ins] = new typename Domain::template UnknownIns<llvm::InsertElementInst>(llvm::dyn_cast<llvm::InsertElementInst>(ins), *this);
                else if (opcode == 63) instructionMap[ins] = new typename Domain::template UnknownIns<llvm::ShuffleVectorInst>(llvm::dyn_cast<llvm::ShuffleVectorInst>(ins), *this);
                else if (opcode == 64) instructionMap[ins] = new typename Domain::template UnknownIns<llvm::ExtractValueInst>(llvm::dyn_cast<llvm::ExtractValueInst>(ins), *this);
                else if (opcode == 65) instructionMap[ins] = new typename Domain::template UnknownIns<llvm::InsertValueInst>(llvm::dyn_cast<llvm::InsertValueInst>(ins), *this);
                else if (opcode == 67) instructionMap[ins] = new typename Domain::template UnknownIns<llvm::FreezeInst>(llvm::dyn_cast<llvm::FreezeInst>(ins), *this);
                else throw std::runtime_error("The instruction class " + (std::string)ins->getOpcodeName() + " with opcode " + std::to_string(opcode) + " does not exist in Vanguard yet.");
            }
            return instructionMap[ins];
        }

        typename Domain::Block *createBlk(const llvm::BasicBlock *block) {
            if(block == nullptr) {
                return nullptr;
            }

            if (blockMap.find(block) == blockMap.end()){
                blockMap[block] = new typename Domain::Block(*this, block);
            }
            return blockMap[block];
        }

        Type *createType(const llvm::Type *t) {
            if(t == nullptr) {
                return nullptr;
            }

            if (typeMap.find(t) == typeMap.end()){
                if (auto integer = llvm::dyn_cast<llvm::IntegerType>(t)){
                    //typeMap[t] = (new IntegerType(*this,*integer));
                    typeMap[t] = new typename Domain::template IntegerType<llvm::IntegerType>(integer, *this);
                }
                else if (auto array = llvm::dyn_cast<llvm::ArrayType>(t)){
                    //typeMap[t] = new ArrayType(*this,*array);
                    typeMap[t] = new typename Domain::template ArrayType<llvm::ArrayType>(array, *this);
                }
                    // else if (auto function = llvm::dyn_cast<llvm::FunctionType>(&t)){
                    //     typeMap[&t] = new FunctionT(*function);
                    // }
                else if (auto pointer = llvm::dyn_cast<llvm::PointerType>(t)){
                    //typeMap[t] = new PointerType(*this,*pointer);
                    typeMap[t] = new typename Domain::template PointerType<llvm::PointerType>(pointer, *this);
                }
                else if (auto structT = llvm::dyn_cast<llvm::StructType>(t)){
                    typeMap[t] = new typename Domain::template StructType<llvm::StructType>(structT, *this);
                }
                else if (auto vector = llvm::dyn_cast<llvm::VectorType>(t)){
                    typeMap[t] = new typename Domain::template ArrayType<llvm::VectorType>(vector, *this);
                }
                else if (t->isVoidTy()){
                    //typeMap[t] = new VoidType(*this,*t);
                    typeMap[t] = new typename Domain::template VoidType<llvm::Type>(t, *this);
                }
                else if (t->isLabelTy()){
                    typeMap[t] = new typename Domain::template LocationType<llvm::Type>(t, *this);
                }
                else {
                    throw std::runtime_error("Given type cannot be translated since it does not exist in vanguard yet.");
                }
            }
            return typeMap[t];
        }

        typename Domain::Value *createVal(const llvm::Value *val) {
            if(val == nullptr) {
                return nullptr;
            }

            if (valueMap.find(val) == valueMap.end()){
                if (auto globalVariable = llvm::dyn_cast<llvm::GlobalVariable>(val)){
                    valueMap[val] = new typename Domain::template Variable<llvm::GlobalVariable>(globalVariable, *this);
                }
                else if (auto argument = llvm::dyn_cast<llvm::Argument>(val)){
                    valueMap[val] = new typename Domain::template Variable<llvm::Argument>(argument, *this);
                }
                else if (auto instVar = llvm::dyn_cast<llvm::Instruction>(val)){
                    valueMap[val] = new typename Domain::template Variable<llvm::Instruction>(instVar, *this);
                }
                else if (auto integer = llvm::dyn_cast<llvm::ConstantInt>(val)){
                    valueMap[val] = new typename Domain::template Literal<llvm::ConstantInt>(integer, *this);
                }
                else if (auto string = llvm::dyn_cast<llvm::ConstantDataSequential>(val)){
                    valueMap[val] = new typename Domain::template Literal<llvm::ConstantDataSequential>(string, *this);
                }
                else if(auto constant = llvm::dyn_cast<llvm::Constant>(val)){
                    valueMap[val] = new typename Domain::template Constant<llvm::Constant>(constant, *this);
                }
                else if(auto loc = llvm::dyn_cast<llvm::BasicBlock>(val)) {
                    valueMap[val] = new typename Domain::template Location<llvm::BasicBlock>(loc, *this);
                }
                else{
                    throw std::runtime_error("Given value cannot be translated since it does not exist in vanguard yet.");
                }
            }
            return valueMap[val];
        }

    protected:
        std::unordered_map<const llvm::Module*, typename Domain::CompilationUnit*> moduleMap;
        std::unordered_map<const llvm::Function*, typename Domain::Function*> functionMap;
        std::unordered_map<const llvm::BasicBlock*, typename Domain::Block*> blockMap;
        std::unordered_map<const llvm::Instruction*, typename Domain::Instruction*> instructionMap;
        std::unordered_map<const llvm::Type*, typename Domain::Type*> typeMap;
        std::unordered_map<const llvm::Value*, typename Domain::Value*> valueMap;
    };
}

#endif //VANGUARD_FACTORY_H
