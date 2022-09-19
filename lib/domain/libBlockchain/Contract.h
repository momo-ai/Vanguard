//
// Created by Jon Stephens on 9/18/22.
//

#ifndef VANGUARD_LIBBLOCKCHAIN_CONTRACT_H
#define VANGUARD_LIBBLOCKCHAIN_CONTRACT_H

#include "Blockchain.h"

namespace vanguard {

    template<class Base, class Domain>
    class Blockchain<Base, Domain>::Contract : public ObjectType<Domain> {
    public:
        Contract(BlockchainModel<Domain> &model, std::string name, std::vector<typename Domain::Function *> fns, std::vector<vanguard::Variable<Domain> *> vars/*, std::vector<BlkType *> inherits,
            std::vector<BlkEnum *> enums, std::vector<BlkStruct *> structs, std::vector<BlkEvent *> events*/) : model(model), contractName(std::move(name)), fns(std::move(fns)), vars(std::move(vars)), ObjectType<Domain>() {
            auto contract = (typename Domain::Contract *) this;
            for(auto fn : this->fns) {
                fn->setContract(contract);
            }
        };

        std::string name() const override {
            return contractName;
        }

        //const Function *findFunction(vanguard::Function &fn) const;

        const std::vector<typename Domain::Function *> &functions() const {
            return fns;
        }

        const std::vector<vanguard::Variable<Domain> *> &variables() const {
            return vars;
        }

        BlockchainModel<Domain> &blockchainModel() {
            return model;
        }

        const llvm::Type *unwrap() const override {
            return nullptr;
        }
        //std::vector<BlkContract *> inherits() const;
    private:
        const std::string contractName;
        BlockchainModel<Domain> &model;
        /*std::vector<BlkUserType *> contractInherits;
        std::vector<BlkEvent *> contractEvents;
        std::vector<BlkEnum *> contractEnums;
        std::vector<BlkStruct *> contractStructs;*/
        std::vector<typename Domain::Function *> fns;
        std::vector<vanguard::Variable<Domain> *> vars;
    };
}


#endif //VANGUARD_CONTRACT_H
