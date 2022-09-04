//
// Created by Jon Stephens on 9/3/22.
//

#ifndef VANGUARD_TOP_H
#define VANGUARD_TOP_H

#include "InstructionClassVisitor.h"

namespace vanguard {
    template <typename Domain>
    class Top : public Domain {
    public:
        class Function;
        class Block;
        class Instruction;

        class CompilationUnit : public Domain::CompilationUnit {
        public:
            template<typename ...Args>
            explicit CompilationUnit(Args&&... args) : Domain::CompilationUnit(std::forward<Args>(args)...) {};

            virtual Function* findFunction(std::string name)  {
                return dynamic_cast<Function *>(this->findFn(name));
            }

            virtual std::vector<Function*> functions()  {
                std::vector<Function *> fns;
                for(auto fn : this->fns()) {
                    fns.push_back(dynamic_cast<Function *>(fn));
                }

                return fns;
            }

        protected:

        };

        class Function : public Domain::Function{
        public:
            template<typename ...Args>
            explicit Function(Args&&... args) : Domain::Function(std::forward<Args>(args)...) {};

            virtual Block* body() const {
                return dynamic_cast<Block *>(this->head());
            }

            virtual std::vector<Instruction*> instructions() const {
                std::vector<Instruction *> ins;
                for(auto i : this->insts()) {
                    ins.push_back(dynamic_cast<Instruction *>(i));
                }

                return ins;
            }

            virtual std::vector<Block *> blocks() const {
                std::vector<Block *> blks;
                for(auto blk : this->blks()) {
                    blks.push_back(dynamic_cast<Block *>(blk));
                }

                return blks;
            }

        protected:

        };

        class Block : public Domain::Block {
        public:
            template<typename ...Args>
            explicit Block(Args&&... args) : Domain::Block(std::forward<Args>(args)...) {};

            virtual Function* parent()  {
                return dynamic_cast<Function *>(this->fn());
            }

            virtual std::unordered_set<Block*> successors()  {
                std::unordered_set<Block *> blks;
                for(auto blk : this->succs()) {
                    blks.insert(dynamic_cast<Block *>(blk));
                }

                return blks;
            }

            virtual std::vector<Instruction*> instructions()  {
                std::vector<Instruction *> ins;
                for(auto i : this->insts()) {
                    ins.push_back(dynamic_cast<Instruction *>(i));
                }

                return ins;
            }

        protected:

        };

        class Instruction : public Domain::Instruction {
        public:
            template<typename ...Args>
            explicit Instruction(Args&&... args) : Domain::Instruction(std::forward<Args>(args)...) {};
            virtual void accept(InstructionClassVisitor<Top<Domain>> &v) const = 0;
        protected:
        };

        template<typename ...Args>
        explicit Top(Args&&... args) : Domain(std::forward<Args>(args)...) {};
    };
}

#endif //VANGUARD_TOP_H
