//
// Created by Jon Stephens on 3/31/22.
//

#ifndef VANGUARD_MEMORYVAL_H
#define VANGUARD_MEMORYVAL_H

#include "llvm/Analysis/MemoryLocation.h"
#include "llvm/IR/Value.h"
#include "Val.h"

namespace vanguard {
    class MemoryVal : public Val {
    public:
        MemoryVal(llvm::Value &val, uint64_t size);
        explicit MemoryVal(llvm::MemoryLocation memLoc);
        const llvm::Value &ptr() const;
        //uint64_t size() const;

        static inline bool classof(const MemoryVal *) { return true; }
        static inline bool classof(const Val *b) {
            if(b->getType() == MEMORY_VAL) { return true; }
            return false;
        }
        friend bool operator==(const MemoryVal& lhs, const MemoryVal& rhs);
        friend bool operator!=(const MemoryVal& lhs, const MemoryVal& rhs);
        llvm::MemoryLocation toMemoryLocation() const;
        bool includes(const MemoryVal &other) const;
        //overloaded fns
        bool operator==(const Val &rhs) const override;
        std::size_t hash() const override;
    private:
        llvm::MemoryLocation loc;

        uint64_t getTaint(const Taint &taint) const override;
        bool setTaint(Taint &taint, uint64_t mask) const override;
        bool addTaint(Taint &taint, uint64_t mask) const override;
        bool untaint(Taint &taint, uint64_t mask) const override;
    };
}

namespace std {
    template <>
    struct hash<vanguard::MemoryVal>
    {
        std::size_t operator()(const vanguard::MemoryVal & t) const
        {
            return t.hash();
        }
    };
}


#endif //VANGUARD_MEMORYVAL_H
