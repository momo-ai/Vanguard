//
// Created by Jon Stephens on 9/18/22.
//

#ifndef VANGUARD_LIBBLOCKCHAIN_INSTRUCTION_H
#define VANGUARD_LIBBLOCKCHAIN_INSTRUCTION_H

#include "Blockchain.h"

namespace vanguard {
    template<typename Base, typename Domain>
    class Blockchain<Base, Domain>::Instruction : public Base::Instruction {
    public:
        template<typename ...Args>
        explicit Instruction(Args&&... args) : Base::Instruction(std::forward<Args>(args)...) {};

        virtual bool isAnyLowLevelCall()  {
            return false;
        }

        virtual bool isLowLevelCall()  {
            return false;
        }

        virtual bool isLowLevelStaticCall()  {
            return false;
        }

        virtual bool isLowLevelDelegateCall()  {
            return false;
        }

        bool writesStorage()  {
            auto contract = this->block()->function()->contract();
            if(contract != nullptr) {
                auto &model = contract->blockchainModel();
                return model.writesStorage(*static_cast<typename Domain::Instruction *>(this));
            }
            return false;
        }

        bool readsStorage()  {
            auto contract = this->block()->function()->contract();
            if(contract != nullptr) {
                auto &model = contract->blockchainModel();
                return model.readsStorage(*static_cast<typename Domain::Instruction *>(this));
            }
            return false;
        }
    };

    template<typename Base, typename Domain>
    template<typename Wrap, typename D>
    class Blockchain<Base, Domain>::CallIns : public Base::template CallIns<Wrap, D> {
    public:
        template<typename ...Args>
        explicit CallIns(Args&&... args) : Base::template CallIns<Wrap, D>(std::forward<Args>(args)...) {};

        bool isAnyLowLevelCall()  override {
            auto contract = this->block()->function()->contract();
            if(contract != nullptr) {
                auto &model = contract->blockchainModel();
                return model.isAnyLowLevelCall(*this);
            }
            return false;
        }

        bool isLowLevelCall()  override {
            auto contract = this->block()->function()->contract();
            if(contract != nullptr) {
                auto &model = contract->blockchainModel();
                return model.isLowLevelCall(*this);
            }
            return false;
        }

        bool isLowLevelStaticCall()  override {
            auto contract = this->block()->function()->contract();
            if(contract != nullptr) {
                auto &model = contract->blockchainModel();
                return model.isLowLevelStaticCall(*this);
            }
            return false;
        }

        bool isLowLevelDelegateCall()  override {
            auto contract = this->block()->function()->contract();
            if(contract != nullptr) {
                auto &model = contract->blockchainModel();
                return model.isLowLevelDelegateCall(*this);
            }
            return false;
        }

        std::vector<typename Domain::Function*> targets() const override {
            auto blk = this->block();
            auto fn = blk->function();
            auto contract = fn->contract();
            //auto contract = this->block()->function()->contract();
            typename Domain::Universe *universe = this->block()->function()->unit()->universe();
            if(contract != nullptr) {
                auto &model = contract->blockchainModel();
                auto callResolver = model.callResolver();
                if(callResolver != nullptr) {
                    auto tgts = callResolver->resolve(*this, *universe);
                    if(!tgts.empty()) {
                        return tgts;
                    }
                }
            }
            return Base::template CallIns<Wrap, D>::targets();
        }
    };
}


#endif //VANGUARD_INSTRUCTION_H
