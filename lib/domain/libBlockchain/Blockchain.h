//
// Created by Jon Stephens on 8/31/22.
//

#ifndef VANGUARD_BLOCKCHAIN_H
#define VANGUARD_BLOCKCHAIN_H

#include <utility>
#include "BlkValue.h"

namespace vanguard {
    template<class Domain> class BlkFunction;

    template<class Domain>
    class Blockchain : public Domain {
    public:
        class Function;

        class Contract : public ObjectType {
        public:
            Contract(UnitFactory &factory, std::string name, std::vector<BlkFunction<Blockchain<Domain>> *> fns, std::vector<Variable *> vars/*, std::vector<BlkType *> inherits,
            std::vector<BlkEnum *> enums, std::vector<BlkStruct *> structs, std::vector<BlkEvent *> events*/) : contractName(std::move(name)), fns(fns), vars(std::move(vars)), ObjectType(factory) {};

            std::string name() const override {
                return contractName;
            }

            //const Function *findFunction(vanguard::Function &fn) const;
            const std::vector<BlkFunction<Blockchain<Domain>> *> &functions() const {
                return fns;
            }

            const std::vector<Variable *> &variables() const {
                return vars;
            }
            //std::vector<BlkContract *> inherits() const;
        private:
            const std::string contractName;
            std::vector<BlkFunction<Blockchain<Domain>> *> fns;
            /*std::vector<BlkUserType *> contractInherits;
            std::vector<BlkEvent *> contractEvents;
            std::vector<BlkEnum *> contractEnums;
            std::vector<BlkStruct *> contractStructs;*/
            std::vector<Variable *> vars;
        };

        class CompilationUnit : public Domain::CompilationUnit {
        public:
            template<typename ...Args>
            explicit CompilationUnit(std::vector<Contract *> contracts, Args&&... args) : unitContracts(contracts), Domain::CompilationUnit(std::forward<Args>(args)...) {};
            std::vector<Contract *> contracts() const {
                return unitContracts;
            }
        private:
            std::vector<Contract *> unitContracts;
        };

        class Function : public Domain::Function {
        public:
            template<typename ...Args>
            explicit Function(Args&&... args) : Domain::Function(std::forward<Args>(args)...) {};

            virtual bool isHelper() const = 0;
        };

        class Instruction : public Domain::Instruction {
        public:
            template<typename ...Args>
            explicit Instruction(Args&&... args) : Domain::Instruction(std::forward<Args>(args)...) {};
        };

        template<typename ...Args>
        explicit Blockchain(Args&&... args) : Domain(std::forward<Args>(args)...) {};

        std::vector<Contract *> contracts() const {
            std::vector<Contract *> contracts;
            for(auto unit : this->units()) {
                auto u = dynamic_cast<Blockchain<Domain>::CompilationUnit *>(unit);
                for(auto contract : u->contracts()) {
                    contracts.push_back(contract);
                }
            }

            return contracts;
        }
    };
}



#endif //VANGUARD_BLOCKCHAIN_H
