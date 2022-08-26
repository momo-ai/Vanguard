#include "IRValidator.h"
#include <unordered_set>
#include <vector>
#include <cassert>
#include <iostream>
#include "../../program/InstructionClasses.h"

namespace vanguard {
    class ValueTrans : public ValueClassVisitor{
    public:
        std::string result;

        void visit(const GlobalVariable &v) override{
            if (v.hasName()){
                result = "GlobalVariable " + v.getName() + " of type " + v.getType()->getName();
            }
            else {
                result = "GlobalVariable of type " + v.getType()->getName();
            }
            result += ", ";
        }

        void visit(const Argument &v) override{
            if (v.hasName()){
                result = "Argument " + v.getName() + " of type " + v.getType()->getName();
            }
            else {
                result = "Argument of type " + v.getType()->getName();
            }
            result+= ", ";
        }

        void visit(const InstructionVariable &v) override{
            if (v.hasName()){
                result = "InstructionVariable " + v.getName() + " of type " + v.getType()->getName();
            }
            else {
                result = "InstructionVariable of type " + v.getType()->getName();
            }
            result+= ", ";
        }

        void visit(const IntegerLiteral &v) override{
            result  = "IntegerLiteral of type " + v.getType()->getName() + " and value: " + std::to_string(v.getValue()) +", ";
        }

        void visit(const StringLiteral &v) override{
            result  = "StringLiteral of type " + v.getType()->getName() + " and value: " + v.getValue() + ". ";
        }

//        void visit(const MemoryAddress &v) override{
//            result = "MemoryAddress of type " + v.getType()->getName() + " and size " + std::to_string(v.getSize()) + ", ";
//        }

        void visit(const Constant &v) override{
            result = "Constant of LLVM ValueID " + std::to_string(v.getLLVMValueID()) + " and type " + v.getType()->getName();
        }

        void visit(const BlockValue &v) override{
            result = "BlockValue of LLVM ValueID " + std::to_string(v.getLLVMValueID()) + " and type " + v.getType()->getName();
        }

    };

    std::string getValueString(const Value &v){
        ValueTrans trans;
        v.accept(trans);
        return trans.result;
    }


    class InstructionTrans: public InstructionClassVisitor{
    public:
        std::string result;
        void visit(const BinaryOperator &inst) override{
            result = "BinaryOperator of BinaryOpClass " + std::to_string(inst.getOpClass()) + " has LHS: " + getValueString((Value&)(*inst.getLHS())) + " and operands: ";
            auto n = inst.getNumOperands();
            assert(n == 2 && "BinaryOperator does not have 2 operands");
            result += getValueString(*inst.getOperand(0)) + " and ";
            result += getValueString(*inst.getOperand(1));
        }

        void visit(const CmpInst &inst) override{
            result = "CmpInst of BinaryOpClass " + std::to_string(inst.getOpClass()) + " has LHS: " + getValueString((Value&)(*inst.getLHS())) + " and operands: ";
            auto n = inst.getNumOperands();
            assert(n == 2 && "CmpInst does not have 2 operands");
            result += getValueString(*inst.getOperand(0)) + " and ";
            result += getValueString(*inst.getOperand(1));
        }

        void visit(const BranchInst &inst) override{
            result = "BranchInst ";
            if (inst.isConditional()){
                result+= "with condition " + getValueString(*inst.getCondition()) + ", ";
            }
            result += " has successors: ";
            for (auto blk : inst.getSuccessors()){
                result += blk->getName() + ", ";
            }
            auto n = inst.getNumOperands();
            if (n != 0) {
                result += "and operands ";
                for (int i = 0; i < n; i++) {
                    result += getValueString(*inst.getOperand(i)) + " ";
                }
            }
        }

        void visit(const IndirectBrInst &inst) override{
            result = "IndirectBrInst " ;
            result += " has successors: ";
            for (auto blk : inst.getSuccessors()){
                result += blk->getName() + ", ";
            }
            auto n = inst.getNumOperands();
            if (n != 0) {
                result += "and operands ";
                for (int i = 0; i < n; i++) {
                    result += getValueString(*inst.getOperand(i)) + " ";
                }
            }
        }

        void visit(const SwitchInst &inst) override{
            result = "SwitchInst with condition "+ getValueString(*inst.getCondition());
            result += " has successors: ";
            for (auto blk : inst.getSuccessors()){
                result += blk->getName() + ", ";
            }
            auto n = inst.getNumOperands();
            if (n != 0) {
                result += "and operands ";
                for (int i = 0; i < n; i++) {
                    result += getValueString(*inst.getOperand(i)) + " ";
                }
            }
        }

        void visit(const UnaryOperator &inst) override{
            result = "UnaryOperator of UnaryOpClass " + std::to_string(inst.getOpClass()) + " has operand " +
                    getValueString(*inst.getUnaryOperand());
        }

        void visit(const CastInst &inst) override{
            result = "CastInst of CastInstClass " + std::to_string(inst.getOpClass()) + " casts from " + inst.getSrcType()->getName() + " to " + inst.getDestType()->getName();
        }

        void visit(const Call &inst) override{
            result = "Call to function " + inst.getTarget()->getName() + " with arguments: ";
            auto args = inst.getArgs();
            for (auto arg: args){
                result += getValueString(*arg) + ", ";
            }
        }

        void visit(const UnreachableInstruction &inst) override{
            result = "UnreachableInstruction: " + inst.error() ;
        }

        void visit(const ReturnInst &inst) override{
            result = "ReturnInst ";
            if (inst.returnsValue()){
                result += "returns value " + getValueString(*inst.returnValue());
            }
            else{
                result += "not returning a value.";
            }
        }

        void visit(const SelectInst &inst) override{
            result = "SelectInst with condition " + getValueString(*inst.getCondition()) + " has true Value " +
                    getValueString(*inst.getTrueValue()) + " and false value " + getValueString(*inst.getFalseValue());
        }

        void visit(const ExtractElementInst &inst) override{
            result = "ExtractElementInst with vector operand: " + getValueString(*inst.getVectorOperand())  + " and index operand " +
                    getValueString(*inst.getIndexOperand());
        }

        void visit(const ExtractValueInst &inst) override{
            result = "ExtractValueInst with aggregrate operand: " + getValueString(*inst.getAggregateOperand()) + " and indices: ";
            for (unsigned i: inst.getIndices()){
                result += std::to_string(i) + ", ";
            }
        }

        void visit(const LoadInst &inst) override{
            result = "LoadInst with pointer operand: " + getValueString(*inst.getPointerOperand());
        }

        void visit(const InsertValueInst &inst) override{
            result = "InsertValueInst inserting " + getValueString(*inst.getInsertedValueOperand()) + " to " +
                    getValueString(*inst.getAggregateOperand()) + " at indices: ";
            for (unsigned i: inst.getIndices()){
                result += std::to_string(i) + ", ";
            }
        }

        void visit(const InsertElementInst &inst) override{
            result = "InsertElementInst inserts value: " + getValueString(*inst.getInsertedElement())  + " to vector: " + getValueString(*inst.getVector()) + " at index " +
                    getValueString(*inst.getIndex());
        }

        void visit(const StoreInst &inst) override{
            result = "StoreInst storing value " + getValueString(*inst.getValueOperand()) + " at pointer " +
                    getValueString(*inst.getPointerOperand());
            assert(inst.getPointerOperandType() == inst.getPointerOperand()->getType() && "Pointer Operand Type not not consistent in StoreInst");
        }

        void visit(const ShuffleVectorInst &inst) override{
            result = "ShuffleVectorInst ";
        }

        void visit(const AllocaInst &inst) override{
            result = "AllocaInst allocating for type: " + inst.getAllocatedType()->getName();
        }

        void visit(const PHINode &inst) override{
            result = "PHINode assigns to variable: " + getValueString(*inst.getLHS()) + " following values based on respective incoming blocks: " ;
            int n = inst.getNumIncomingValues();
            auto values = inst.getIncomingValues();
            auto blocks = inst.getIncomingBlocks();
            for (int i = 0; i < n; i++){
                result += "(" + std::to_string(i+1) + ") block: ";
                result += blocks[i]->getName();
                result += ", value: " + getValueString(*values[i]);
            }
        }

        void visit(const GetElementPtrInst &inst) override{
            result = "GetElementPtrInst assigns to: " + getValueString(*inst.getLHS()) + " getting value at pointer " +
                    getValueString(*inst.getPointerOperand());
        }

        void visit(const FreezeInst &inst) override{
            result = "FreezeInst assigns to " + getValueString(*inst.getLHS());
        }
    };

    std::string getInstructionString(const Instruction &v){
        InstructionTrans trans;
        v.accept(trans);
        return trans.result;
    }


    void IRValidator::registerAnalyses() { }
    void IRValidator::startDetection() {
        totBlks = 0;
        totFns = 0;
        totIns = 0;
    }

    std::string IRValidator::name() {
        return "irValidator";
    }

    void IRValidator::countBody(Block *blk) {
        assert(blk != nullptr && "Function does not have a body");
        assert(blk->isEntryBlock() && "Fn body not marked as entry block");

        std::unordered_set<Block *> seen = { blk };
        std::vector<Block *> worklist = { blk };

        while(!worklist.empty()) {
            Block *curBlk = worklist.back();
            worklist.pop_back();

            totBlks++;

            for(auto ins : curBlk->getInstructionsList()) {
                assert(curBlk == ins->getBlock() && "Block does not match instruction block");
                totIns++;
            }

            for(auto next : curBlk->getAllSuccessors()) {
                if(next != nullptr && seen.find(next) == seen.end()) {
                    seen.insert(next);
                    worklist.push_back(next);
                }
            }
        }
    }

    void IRValidator::detect(CompilationUnit &unit) {
        moduleName = unit.getModuleName();
        sourceFileName = unit.getSourceFileName();

        for(auto fn : unit.getAllFunctions()) {
            totFns++;
            if(fn->hasBody()) {
                auto body = fn->getBody();
                assert(body->getFunction() == fn && "Function does not match block function");
                assert(body->isEntryBlock() == true && "Not an entry block.");
                countBody(body);
            }
        }

        std::cout << "\n ---- Listing global variables with their types ---- \n";
        for (auto globalVariableValue: unit.getAllGlobalVariables()){
            auto globalVariable = llvm::dyn_cast<GlobalVariable>(globalVariableValue);
            if (globalVariable->hasName()) {
                auto globalVariableFromName = (GlobalVariable *)unit.getGlobalVariable(globalVariable->getName());
                assert(globalVariableFromName == globalVariable && "globalVariable and globalVariableFromName ");
                assert(globalVariableFromName != nullptr && "Global variable from Name is null.");
                std::cout << globalVariableFromName->getName() << " : " << (globalVariableFromName->getType())->getName() << "\n";
            }
        }

        std::cout << "\n ---- Listing functions with their signature ---- \n";
        std::vector< std::string > functionsNames = {};
        std::vector< std::list< Argument* > > functionsArguments = {};
        std::vector< std::list< Type* > > functionsArgumentTypes = {};
        std::vector< Type* > functionReturnTypes = {};
        int numFunctions = 0;
        for (auto function: unit.getAllFunctions()){
            auto functionFromName = unit.getFunction(function->getName());
            assert(functionFromName != nullptr && "Function from name is null.");
            assert(function == functionFromName && "Function and function from name are not the same." );
            functionsNames.push_back(function->getName());
            functionsArguments.push_back(function->getParams());
            functionsArgumentTypes.push_back(function->getParamTypes());
            functionReturnTypes.push_back(function->getReturnType());
            numFunctions++;
        }
        for(int i = 0; i < numFunctions; i++){
            std::cout << functionsNames[i] << " : (";
            auto itr1 = functionsArguments[i].begin();
            auto itr2 = functionsArgumentTypes[i].begin();
            for( ; itr1 != functionsArguments[i].end() && itr2 != functionsArgumentTypes[i].end(); ++itr1, ++itr2){
                if ((*itr1)->hasName()){
                    std::cout << (*itr1)->getName() << " : ";
                }
                std::cout << (*itr2)->getName() << ", ";
            }
            std::cout << ") -> " << functionReturnTypes[i]->getName() << "\n";
        }


        std::cout << "---- Listing all Instructions with their types ---- \n";
        for(auto fn : unit.getAllFunctions()) {
            std::cout << fn->getName() << ":\n";
            std::list<Instruction*> instructionsList = fn->getInstructionsList();
            if(!instructionsList.empty()) {
                for (auto instruction: instructionsList) {
//                    std::cout << instruction->getName() << " : " << instruction->getInstructionType() << "\n";
                    std::cout << getInstructionString(*instruction) << "\n";

                }
            }
        }
    }

    void IRValidator::report() {
        std::cout << "Module Name: " << moduleName << "\n";
        std::cout << "Source File Name: " << sourceFileName << "\n";
        std::cout << "Statistics:\n";
        std::cout << "# Functions: " << totFns << "\n";
        std::cout << "# Basic Blocks: " << totBlks << "\n";
        std::cout << "# Instructions: " << totIns << "\n";
    }
}