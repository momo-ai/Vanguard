//
// Created by Jon Stephens on 4/10/22.
//

#include "../include/Blockchain.h"
#include "../include/BlockchainToLLVM.h"

namespace blockchain {
    Blockchain::~Blockchain() {
        deleter(allContracts);
        delete blkTollvm;
    }

    std::string Blockchain::getThing() {
        return "found thing!";
    }

    bool Blockchain::isContractFunction(vanguard::Function &fn) const {
        return findDeclaringContract(fn) != nullptr;
    }

    const vector<BlkContract *> &Blockchain::contracts() const {
        return *allContracts;
    }

    const BlkFunction *Blockchain::findFunction(vanguard::Function &fn) const {
        for(auto contract : *allContracts) {
            const BlkFunction *blkFn = contract->findFunction(fn);
            if(blkFn != nullptr) {
                return blkFn;
            }
        }

        return nullptr;
    }

    const BlkContract *Blockchain::findDeclaringContract(vanguard::Function &fn) const {
        for(auto contract : *allContracts) {
            if(contract->isContractFunction(fn)) {
                return contract;
            }
        }

        return nullptr;
    }

    bool Blockchain::isAnyExternalCall(vanguard::Function &fn) const  {
        return blkTollvm->isAnyExternalCall(fn);
    }

    bool Blockchain::isCall(vanguard::Function &fn) const {
        return blkTollvm->isCall(fn);
    }

    bool Blockchain::isStaticCall(vanguard::Function &fn) const {
        return blkTollvm->isStaticCall(fn);
    }

    bool Blockchain::isDelegateCall(vanguard::Function &fn) const {
        return blkTollvm->isDelegateCall(fn);
    }

    bool Blockchain::resolvesCalls() {
        // TODO: Implement this
        return false;
    }

    std::list<vanguard::CallEdge*> Blockchain::getCallees(vanguard::Context context, vanguard::CallInstruction ins) {
        std::list<vanguard::CallEdge*> res;
        return res;
    }

    bool Blockchain::hasAdditionalStorage() {
        // TODO: Implement this
        return true;
    }

    std::list<vanguard::Value*> Blockchain::getAdditionalStorage() {
        std::list<vanguard::Value*> res;
        for(auto contract : *allContracts) {
            for(auto var : contract->variables()) {
                res.push_back(var);
            }
        }
        return res;
    }

    std::list<vanguard::Value*> Blockchain::getStorageReads(vanguard::Instruction& ins) {
        std::list<vanguard::Value*> res;
        for(auto contract: *allContracts) {
            for(auto var : contract->variables()) {
                if(var->readBy(ins)) {
                    res.push_back(var);
                }
            }
        }
        return res;
    }

    std::list<vanguard::Value*> Blockchain::getStorageWrites(vanguard::Instruction& ins) {
        std::list<vanguard::Value*> res;
        for(auto contract: *allContracts) {
            for(auto var : contract->variables()) {
                if(var->writtenBy(ins)) {
                    res.push_back(var);
                }
            }
        }
        return res;
    }

}