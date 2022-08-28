//
// Created by Jon Stephens on 8/14/22.
//

#include "StatGen.h"
#include <unordered_set>
#include <vector>
#include <cassert>
#include <iostream>

#include "../../domain/libBlockchain/include/Blockchain.h"

namespace vanguard {
    std::vector<Requirement *> StatGen::registerAnalyses() {
        return {};
    }
    void StatGen::startDetection() {
        totBlks = 0;
        totFns = 0;
        totIns = 0;
    }

    std::string StatGen::name() {
        return "statGen";
    }

    void StatGen::countBody(Block *blk) {
        assert(blk != nullptr && "Function does not have a body");
        assert(blk->isEntry() && "Fn body not marked as entry block");

        std::unordered_set<Block *> seen = { blk };
        std::vector<Block *> worklist = { blk };

        while(!worklist.empty()) {
            Block *curBlk = worklist.back();
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

    void StatGen::detect(CompilationUnit &unit) {
        for(auto fn : unit.functions()) {
            totFns++;
            if(fn->hasBody()) {
                auto body = fn->body();
                assert(body->parent() == fn && "Function does not match block function");

                countBody(body);
            }
        }
    }

    void StatGen::report() {
        std::cout << "Statistics:" << std::endl;
        std::cout << "# Functions: " << totFns << std::endl;
        std::cout << "# Basic Blocks: " << totBlks << std::endl;
        std::cout << "# Instructions: " << totIns << std::endl;
        std::cout << blockchain::Blockchain::getThing() << std::endl;
    }
}