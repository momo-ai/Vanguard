//
// Created by Jon Stephens on 8/20/22.
//

#ifndef VANGUARD_BASE_H
#define VANGUARD_BASE_H

#include <vector>
#include <llvm/IR/Module.h>
#include <list>
#include <unordered_set>
#include "InstructionClassVisitor.h"

namespace vanguard {
    enum InstructionClassEnum {
        BRANCH,
        RETURN,
        ERROR,
        EXPRESSION_BEGIN,
        BIN_OP = EXPRESSION_BEGIN,
        UN_OP,
        CALL,
        CAST,
        TERNARY,
        ASSIGNMENT,
        UNKNOWN,
        EXPRESSION_END = UNKNOWN
    };

    template<typename Domain> class Variable;

    template <typename Domain>
    class Base {
    public:
        class Universe;
        class Factory;
        class CompilationUnit;
        class Function;
        class Block;
        class Instruction;
        template<typename Wrap, typename D = void> class BranchIns;
        template<typename Wrap, typename D = void> class ReturnIns;
        template<typename Wrap, typename D = void> class ErrorIns;
        template<typename Wrap, typename D = void> class AssignIns;
        template<typename Wrap, typename D = void> class BinaryOpIns;
        template<typename Wrap, typename D = void> class UnaryOpIns;
        template<typename Wrap, typename D = void> class CallIns;
        template<typename Wrap, typename D = void> class CastIns;
        template<typename Wrap, typename D = void> class TernaryIns;
        template<typename Wrap, typename D = void> class UnknownIns;

        class Value;
        template<typename Wrap, typename D = void> class Variable;
        template<typename Wrap, typename D = void> class Constant;
        template<typename Wrap, typename D = void> class Literal;
        template<typename Wrap, typename D = void> class Pointer;
        template<typename Wrap, typename D = void> class MemoryRegion;
        template<typename Wrap, typename D = void> class Location;

        class Type;
        template<typename Wrap, typename D = void> class IntegerType;
        template<typename Wrap, typename D = void> class ArrayType;
        template<typename Wrap, typename D = void> class VectorType;
        template<typename Wrap, typename D = void> class PointerType;
        template<typename Wrap, typename D = void> class StructType;
        template<typename Wrap, typename D = void> class VoidType;
        template<typename Wrap, typename D = void> class LocationType;


        /*class CompilationUnit {
        public:
            explicit CompilationUnit(Factory &factory, const llvm::Module* mod);
            CompilationUnit(const CompilationUnit&) = delete;
            std::string name();
            std::string sourceFile();
            typename Derived::Value* findGlobalVariable(std::string name);
            virtual std::list<typename Derived::Value*> globalVariables();
            virtual typename Derived::Function* findFunction(std::string name) const;
            virtual std::list<typename Derived::Function *> functions() const;
            const llvm::Module* unwrap();
        protected:
            //typename Domain::Function* findFn(std::string name) const;
            //virtual std::list<typename Domain::Function *> fns() const;
            Factory &factory;
        private:
            const llvm::Module* module;
        };*/

        /*class Function {
        public:
            explicit Function(Factory &factory, const llvm::Function *func);
            Function(const Function&) = delete;
            virtual std::string name() const;
            virtual std::vector<vanguard::Variable<Derived>*> params() const;
            virtual typename Derived::Type* returnType() const;
            virtual bool hasBody() const;
            //virtual CompilationUnit* unit() const = 0;
            const llvm::Function *unwrap();
            virtual typename Derived::CompilationUnit *unit() const ;
            virtual typename Derived::Block* body() const ;
            virtual std::vector<typename Derived::Instruction*> instructions() const ;
            virtual std::vector<typename Derived::Block *> blocks() const;
        protected:
            const llvm::Function *function;
            Factory &factory;
        };*/

        /*class Block {
        public:
            explicit Block(Factory &factory, const llvm::BasicBlock *block);
            Block(const Block&) = delete;
            virtual std::string name();
            virtual bool isEntry();
            virtual typename Derived::Function* function() const;
            virtual const llvm::BasicBlock* unwrap();
            virtual std::list<typename Derived::Instruction *> instructions() const ;
            virtual std::unordered_set<typename Derived::Block *> successors() const;
        protected:
            //virtual std::list<typename Domain::Instruction *> insts() const ;
            //virtual std::unordered_set<typename Domain::Block *> succs() const;

            const llvm::BasicBlock* block;
            Factory &factory;
        };*/


        /*class Instruction {
        public:
            explicit Instruction(Factory &factory, const llvm::Instruction *ins) : ins(ins), factory(factory) {};
            static inline bool classof(const Instruction &) { return true; }
            static inline bool classof(const Instruction *) { return true; }

            virtual InstructionClassEnum instructionClass() const = 0;
            virtual void accept(InstructionClassVisitor<Derived> &v) const = 0;
            virtual std::string name() const {
                return ins->getName().str();
            }
            virtual bool willReturn() const {
                return ins->willReturn();
            }
            virtual typename Derived::Value* operandAt(unsigned i) const {
                return factory.createVal(ins->getOperand(i));
            }
            virtual unsigned numOperands() const {
                return ins->getNumOperands();
            }
            virtual const llvm::Instruction &unwrap() const {
                return *ins;
            }
            //virtual std::vector<Value *> reads();
            //virtual std::vector<Value *> writes();
            virtual typename Derived::Block* block() const {
                return factory.createBlk(ins->getParent());
            }
        protected:
            const llvm::Instruction* ins;
            Factory &factory;
        };*/

        //explicit Universe(UnitFactory &factory, std::vector<CompilationUnit *>  units);
        //const std::vector<CompilationUnit *> &units() const;

        /*Universe(Factory &factory, std::vector<CompilationUnit *>  units) : fact(factory), programUnits(std::move(units)) {}

        const std::vector<CompilationUnit *> &units() const {
            return programUnits;
        }



        decltype(auto) factory() {
            return static_cast<typename Domain::Factory &>(fact);
        }

    protected:

        Factory &fact;
    private:
        std::vector<CompilationUnit *> programUnits;*/
    };
}



#endif //VANGUARD_BASE_H
