//
// Created by Jon Stephens on 3/31/22.
//

#include "MemoryVal.h"
#include "Taint.h"

namespace vanguard {
    MemoryVal::MemoryVal(llvm::Value &val, uint64_t size) : Val(MEMORY_VAL) {
        loc = MemoryLocation(&val, llvm::LocationSize::precise(size));
    }

    MemoryVal::MemoryVal(llvm::MemoryLocation memLoc) : loc(memLoc), Val(MEMORY_VAL) {}

    bool operator==(const MemoryVal& lhs, const MemoryVal& rhs) {
        if(lhs.loc.Size.hasValue() == rhs.loc.Size.hasValue()) {
            if(lhs.loc.Size.hasValue()) {
                return lhs.loc.Ptr == rhs.loc.Ptr && lhs.loc.Size.getValue() == rhs.loc.Size.getValue();
            }
            else {
                return lhs.loc.Ptr == rhs.loc.Ptr;
            }
        }
        return false;
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
        //return loc.Ptr == other.loc.&& memSize >= other.memSize;
        if(loc.Ptr == other.loc.Ptr) {
            return loc.Size.unionWith(other.loc.Size) == loc.Size;
        }

        return false;
    }

    const llvm::Value &MemoryVal::ptr() const {
        return *loc.Ptr;
    }

    /*uint64_t MemoryVal::size() const {
        return memSize;
    }*/

    llvm::MemoryLocation MemoryVal::toMemoryLocation() const {
        return loc;
    }

    /*
     * Overloaded Functions
     */
    std::size_t MemoryVal::hash() const {
        if(loc.Size.hasValue()) {
            return ((std::size_t) loc.Ptr) * loc.Size.getValue();
        }
        return ((std::size_t) loc.Ptr);
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