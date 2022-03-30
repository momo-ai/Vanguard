//
// Created by Jon Stephens on 3/28/22.
//

#include "ReadWriteRetriever.h"
#include "RegisterVal.h"

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

    ReadWriteInfo ReadWriteRetriever::retrieve(const Instruction &ins) {
        ReadWriteInfo info;
        info.requiresUpdate = false;

        for(auto &use : ins.uses()) {
            info.reads.push_back(new RegisterVal(*use.get()));
        }

        info.writes.push_back(new RegisterVal((Value &) ins));
        return info;
    }
};


