#include "IRValidator.h"
#include <unordered_set>
#include <vector>
#include <cassert>
#include <iostream>
#include "../../program/WrappedInstructions.h"
#include <program/Function.cpp>
#include <program/CompilationUnit.h>

namespace vanguard {
    static bool debug_ir_validator = false;

    class ValueTrans : public ValueClassVisitor{
    public:
        std::string result;

        void visit(const GlobalVariable &v) override{
            if (v.hasName()){
                result = "GlobalVariable " + v.name() + " of type " + v.type()->name();
            }
            else {
                result = "GlobalVariable of type " + v.type()->name();
            }
            result += ", ";
        }

        void visit(const Argument &v) override{
            if (v.hasName()){
                result = "Argument " + v.name() + " of type " + v.type()->name();
            }
            else {
                result = "Argument of type " + v.type()->name();
            }
            result+= ", ";
        }

        void visit(const InstructionVariable &v) override{
            if (v.hasName()){
                result = "InstructionVariable " + v.name() + " of type " + v.type()->name();
            }
            else {
                result = "InstructionVariable of type " + v.type()->name();
            }
            result+= ", ";
        }

        void visit(const IntegerLiteral &v) override{
            result  = "IntegerLiteral of type " + v.type()->name() + " and value: " + std::to_string(v.value()) + ", ";
        }

        void visit(const StringLiteral &v) override{
            result  = "StringLiteral of type " + v.type()->name() + " and value: " + v.value() + ". ";
        }

        void visit(const Pointer &v) override {
            result = "found pointer";
        }

        void visit(const MemoryRegion &v) override{
            result = "MemoryRegion of type " + v.type()->name() + " and size " + std::to_string(v.size()) + ", ";
        }

        void visit(const Constant &v) override{
            result = "Constant of LLVM ValueID " + std::to_string(v.getLLVMValueID()) + " and type " + v.type()->name();
        }

        void visit(const Location &v) override{
            result = "BlockValue of type " +
                    v.type()->name();
        }

        void visit(const Variable &v) override {
            result = "Variable of type " +
                     v.type()->name();
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
        void visit(const BinaryOpExpr &inst) override{
            auto op = inst.op();
            auto varResult = inst.result();
            result = "BinaryIns of BinaryOpClass " + std::to_string(op) + " has LHS: " + getValueString(*varResult) + " and operands: ";
            auto n = inst.numOperands();
            assert(n == 2 && "BinaryIns does not have 2 operands");
            result += getValueString(*inst.operand(0)) + " and ";
            result += getValueString(*inst.operand(1));
        }

        void visit(const Branch &inst) override{
            result = "BranchIns ";
            if (inst.isConditional()){
                result+= "with condition " + getValueString(*inst.condition()) + ", ";
            }
            result += " has successors: ";
            for (auto blk : inst.targets()){
                result += blk->name() + ", ";
            }
            auto n = inst.numOperands();
            if (n != 0) {
                result += "and operands ";
                for (int i = 0; i < n; i++) {
                    result += getValueString(*inst.operand(i)) + " ";
                }
            }
        }

        void visit(const UnaryOpExpr &inst) override{
            result = "UnaryIns of UnaryOpClass " + std::to_string(inst.op()) + " has operand " +
                    getValueString(*inst.operand());
        }

        void visit(const CastExpr &inst) override{
            result = "CastIns casts to " + inst.castTo()->name() ;
        }

        void visit(const CallExpr &inst) override{
            result = "Call to function " + inst.target()->name() + " with arguments: ";
            auto args = inst.args();
            for (auto arg: args){
                result += getValueString(*arg) + ", ";
            }
        }

        void visit(const Error &inst) override {
            result = "UnreachableIns: " + inst.msg() ;
        }

        void visit(const Return &inst) override {
            result = "ReturnIns ";
            if (inst.returnsValue()){
                result += "returns value " + getValueString(*inst.value());
            }
            else{
                result += "not returning a value.";
            }
        }

        void visit(const TernaryExpr &inst) override{
            result = "SelectIns with condition " + getValueString(*inst.condition()) + " has true Value " +
                    getValueString(*inst.trueValue()) + " and false value " + getValueString(*inst.falseValue());
        }

        void visit(const Assignment &inst) override {
            result = "assigns " + getValueString(*inst.result());
        }

        void visit(const UnknownExpr &inst) override {
            result = "Unknown expression";
        }
    };

    std::string getInstructionString(const Universe::Instruction &v){
        InstructionTrans trans;
        v.accept(trans);
        return trans.result;
    }


    std::vector<Requirement *> IRValidator::registerAnalyses() {
        return {};
    }
    void IRValidator::startDetection() {
        totBlks = 0;
        totFns = 0;
        totIns = 0;
    }

    std::string IRValidator::name() {
        return "irValidator";
    }

    void IRValidator::countBody(Universe::Block *blk) {
        assert(blk != nullptr && "Function does not have a body");
        assert(blk->isEntry() && "Fn body not marked as entry block");

        std::unordered_set<Universe::Block *> seen = { blk };
        std::vector<Universe::Block *> worklist = { blk };

        while(!worklist.empty()) {
            Universe::Block *curBlk = worklist.back();
            worklist.pop_back();

            totBlks++;

            for(auto ins : curBlk->instructions()) {
                assert(curBlk == ins->parent() && "Block does not match instruction block");
                totIns++;
            }

            for(auto next : curBlk->successors()) {
                if(next != nullptr && seen.find(next) == seen.end()) {
                    seen.insert(next);
                    worklist.push_back(next);
                }
            }
        }
    }

    void IRValidator::detect(Universe::CompilationUnit &unit) {
        moduleName = unit.name();
        sourceFileName = unit.sourceFile();

        for(auto fn : unit.functions()) {
            totFns++;
            if(fn->hasBody()) {
                auto body = fn->body();
                assert(body->parent() == fn && "Function does not match block function");
                assert(body->isEntry() == true && "Not an entry block.");
                countBody(body);
            }
        }

        if(debug_ir_validator){
            std::cout << "\n ---- Listing global variables with their types ---- \n";
        }
        for (auto globalVariableValue: unit.globalVariables()){
            auto globalVariable = llvm::dyn_cast<GlobalVariable>(globalVariableValue);
            if (globalVariable->hasName()) {
                auto globalVariableFromName = (GlobalVariable *) unit.findGlobalVariable(globalVariable->name());
                assert(globalVariableFromName == globalVariable && "globalVariable and globalVariableFromName ");
                assert(globalVariableFromName != nullptr && "Global variable from Name is null.");
                auto globalVariableName = globalVariableFromName->name();
                auto globalVariableType = (globalVariableFromName->type())->name();
                if (debug_ir_validator) {
                    std::cout << globalVariableName << " : " << globalVariableType << "\n";
                }
            }
        }

        if (debug_ir_validator) {
            std::cout << "\n ---- Listing functions with their signature ---- \n";
        }
        std::vector< std::string > functionsNames = {};
        std::vector< std::list< Argument* > > functionsArguments = {};
        std::vector< Type* > functionReturnTypes = {};
        int numFunctions = 0;
        for (auto function: unit.functions()){
            auto functionFromName = unit.findFunction(function->name());
            assert(functionFromName != nullptr && "Function from name is null.");
            assert(function == functionFromName && "Function and function from name are not the same." );
            functionsNames.push_back(function->name());
            functionsArguments.push_back(function->params());
            functionReturnTypes.push_back(function->returnType());
            numFunctions++;
        }
        for(int i = 0; i < numFunctions; i++){
            auto funcName = functionsNames[i];
            if (debug_ir_validator) {
                std::cout << functionsNames[i] << " : (";
            }
            auto itr1 = functionsArguments[i].begin();
            for( ; itr1 != functionsArguments[i].end(); ++itr1){
                if ((*itr1)->hasName()){
                    auto argName = (*itr1)->name();
                    if (debug_ir_validator){
                        std::cout << argName << " : ";
                    }
                }
                auto arg_type_name = (*itr1)->type()->name();
                if (debug_ir_validator) {
                    std::cout << arg_type_name << ", ";
                }
            }
            auto ret_type = functionReturnTypes[i]->name();
            if (debug_ir_validator) {
                std::cout << ") -> " << ret_type << "\n";
            }
        }

        if(debug_ir_validator) {
            std::cout << "---- Listing all Instructions with their types ---- \n";
        }
        for(auto fn : unit.functions()) {
            if (debug_ir_validator) {
                std::cout << fn->name() << ":\n";
            }
            std::list<Universe::Instruction*> instructionsList = fn->instructions();
            if(!instructionsList.empty()) {
                for (auto instruction: instructionsList) {
                    std::string instString = getInstructionString(*instruction);
                    if (debug_ir_validator) {
                        std::cout << instString << "\n";
                    }
                }
            }
        }
    }

    void IRValidator::report() {
        if (debug_ir_validator) {
            std::cout << "Module Name: " << moduleName << "\n";
            std::cout << "Source File Name: " << sourceFileName << "\n";
            std::cout << "Statistics:\n";
            std::cout << "# Functions: " << totFns << "\n";
            std::cout << "# Basic Blocks: " << totBlks << "\n";
            std::cout << "# Instructions: " << totIns << "\n";
        }
        std::cout << "IR validated successfully! \n";
    }
}