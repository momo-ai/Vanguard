//
// Created by Jon Stephens on 3/31/22.
//

#include "MemoryVal.h"
#include "Taint.h"

namespace vanguard {
    MemoryVal::MemoryVal(const llvm::Value &ptr, uint64_t size) : memPtr(&ptr), memSize(size), Val(MEMORY_VAL) {}

    bool operator==(const MemoryVal& lhs, const MemoryVal& rhs) {
        return lhs.memPtr == rhs.memPtr && lhs.memSize == rhs.memSize;
    }

    bool operator!=(const MemoryVal& lhs, const MemoryVal& rhs) {
        return !(lhs == rhs);
    }

    bool MemoryVal::operator==(const Val &rhs) const {
        if(llvm::isa<const MemoryVal>(rhs)) {
            auto &v = llvm::cast<const MemoryVal>(rhs);
            return *this == v;
        }

        return false;
    }

    bool MemoryVal::includes(const MemoryVal &other) const {
        return memPtr == other.memPtr && memSize >= other.memSize;
    }

    const llvm::Value &MemoryVal::ptr() const {
        return *memPtr;
    }

    uint64_t MemoryVal::size() const {
        return memSize;
    }

    llvm::MemoryLocation MemoryVal::toMemoryLocation() const {
        return llvm::MemoryLocation(memPtr, llvm::LocationSize::precise(memSize));
    }

    /*
     * Overloaded Functions
     */
    std::size_t MemoryVal::hash() const {
        return ((std::size_t) memPtr) * memSize;
    }


    uint64_t MemoryVal::getTaint(const Taint &taint) const {
        return taint.getMemTaint(*this);
    }

    bool MemoryVal::setTaint(Taint &taint, uint64_t mask) const {
        return taint.setMemTaint(*this, mask);
    }

    bool MemoryVal::addTaint(Taint &taint, uint64_t mask) const {
        return taint.addMemTaint(*this, mask);
    }

    bool MemoryVal::untaint(Taint &taint, uint64_t mask) const {
        return taint.untaintMem(*this, mask);
    }
}