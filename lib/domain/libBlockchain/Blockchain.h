//
// Created by Jon Stephens on 8/31/22.
//

#ifndef VANGUARD_BLOCKCHAIN_H
#define VANGUARD_BLOCKCHAIN_H

#include <utility>

namespace vanguard {
    template<class Domain>
    class Blockchain : public Domain {
    public:
        class Function;
        //class Block;
        //class Instruction;

        class Contract {
        };

        class Function : public Domain::Function {
        public:
            template<typename ...Args>
            explicit Function(Args&&... args) : Domain::Function(std::forward<Args>(args)...) {};
        protected:
        };

        /*class Block : public Domain::Block {
        public:
            template<typename ...Args>
            explicit Block(Args&&... args) : Domain::Block(std::forward<Args>(args)...) {};
        };

        class Instruction : public Block::Instruction {
        public:
            template<typename ...Args>
            explicit Instruction(Args&&... args) : Domain::Instruction(std::forward<Args>(args)...) {};
        };*/

        explicit Blockchain(UnitFactory &factory, const std::vector<std::unique_ptr<llvm::Module>>& modules) : Domain(factory, modules) {};
    };
}



#endif //VANGUARD_BLOCKCHAIN_H
