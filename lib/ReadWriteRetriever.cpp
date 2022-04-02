//
// Created by Jon Stephens on 3/28/22.
//

#include "ReadWriteRetriever.h"
#include "RegisterVal.h"
#include "MemoryVal.h"

namespace vanguard {
    ReadWriteInfo::~ReadWriteInfo() {
        for(auto read : reads) {
            delete read;
        }
        reads.clear();
        for(auto write : writes) {
            delete write;
        }
        writes.clear();
    }

    ReadWriteInfo ReadWriteRetriever::get(const LoadInst &ins) {
        ReadWriteInfo info = get((const Instruction &) ins);
        info.reads.push_back(new MemoryVal(llvm::MemoryLocation::get(&ins)));
        return info;
    }

    ReadWriteInfo ReadWriteRetriever::get(const StoreInst &ins) {
        ReadWriteInfo info = get((const Instruction &) ins);
        info.writes.push_back(new MemoryVal(llvm::MemoryLocation::get(&ins)));
        return info;
    }

    ReadWriteInfo ReadWriteRetriever::get(const Instruction &ins) {
        ReadWriteInfo info;
        info.requiresUpdate = false;

        for(auto &use : ins.operands()) {
            info.reads.push_back(new RegisterVal(*use.get()));
        }

        info.writes.push_back(new RegisterVal((Value &) ins));
        return info;
    }

    ReadWriteInfo ReadWriteRetriever::retrieve(const Instruction &ins) {
        switch(ins.getOpcode()) {
            case llvm::Instruction::Store: {
                auto &store = cast<const StoreInst>(ins);
                return get(store); }
            case llvm::Instruction::Load: {
                auto &load = cast<const LoadInst>(ins);
                return get(load); }
        }

        return get(ins);
    }
};


