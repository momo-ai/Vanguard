//
// Created by Jon Stephens on 3/31/22.
//

#include "MemoryTaint.h"
#include <iostream>

using namespace blockchain;

namespace vanguard {
    /*
     * alias analysis is only null on declaration, in that case pretend like no memory is aliased
     */
    MemoryTaint::MemoryTaint(llvm::Function &taintFn, AAWrapper &aa) : fn(taintFn),  aaWrapper(aa) {}

    std::vector<std::pair<const MemoryVal *, uint64_t>> MemoryTaint::getMemTaint() const {
        std::vector<std::pair<const MemoryVal *, uint64_t>> tainted;

        for(auto &entry : memTaint) {
            tainted.emplace_back(&entry.first, entry.second);
        }

        return tainted;
    }

    /*
     * add taint to all aliased memory locations
     */
    bool MemoryTaint::addMemTaint(const MemoryVal &v, uint64_t mask) {
        bool modified = (memTaint[v] & mask) != mask;
        memTaint[v] |= mask;

        if(aaWrapper.noAlias(fn)) {
            for(auto &entry : memTaint) {
                if(v.includes(entry.first) || entry.first.includes(v)) {
                    if((entry.second & mask) != mask) {
                        entry.second |= mask;
                        modified = true;
                    }
                }
            }

            return modified;
        }

        for(auto &entry : memTaint) {
            llvm::AAResults *alias = aaWrapper.request(fn);
            if(alias->alias(entry.first.toMemoryLocation(), v.toMemoryLocation())) {
                if((memTaint[v] & mask) != mask) {
                    modified = true;
                    entry.second |= mask;
                }
            }
        }

        return modified;
    }

    /*
     * untaint all subregions
     */
    bool MemoryTaint::untaintMem(const MemoryVal &v, uint64_t mask) {
        bool modified = false;

        for(auto &entry : memTaint) {
            if(v.includes(entry.first)) {
                if((entry.second & mask) != 0) {
                    entry.second &= ~mask;
                    modified = true;
                }
            }
        }

        return modified;
    }

    /*
     * get taint on location or all aliased locations
     */
    uint64_t MemoryTaint::getMemTaint(const MemoryVal &v) const {
        if(memTaint.find(v) != memTaint.end()) {
            return memTaint.at(v);
        }

        if(aaWrapper.noAlias(fn)) {
            uint64_t taint = 0;
            for(auto &entry : memTaint) {
                if(v.includes(entry.first)) {
                    taint |= entry.second;
                }
            }

            return taint;
        }

        uint64_t taint = 0;
        for(auto &entry : memTaint) {
            llvm::AAResults *alias = aaWrapper.request(fn);
            if(alias->alias(entry.first.toMemoryLocation(), v.toMemoryLocation())) {
                taint |= entry.second;
            }
        }

        return taint;
    }

    /*
     * Set taint on any subregion and add taint to all aliases
     */
    bool MemoryTaint::setMemTaint(const MemoryVal &v, uint64_t mask) {
        bool modified = memTaint[v] != mask;
        memTaint[v] = mask;

        for(auto &entry : memTaint) {
            if(v.includes(entry.first)) {
                if(entry.second != mask) {
                    entry.second = mask;
                    modified = true;
                }
            }
        }

        if(aaWrapper.noAlias(fn)) {
            return modified;
        }

        return addMemTaint(v, mask) || modified;
    }

}