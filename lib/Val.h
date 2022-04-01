//
// Created by Jon Stephens on 3/28/22.
//

#ifndef VANGUARD_VAL_H
#define VANGUARD_VAL_H

#include <llvm/IR/Function.h>
#include <unordered_set>
#include <vector>
#include "TaintLabel.h"

namespace vanguard {
    class Taint;

    enum ValType {
        REGISTER_VAL,
        MEMORY_VAL
    };

    class Val {
    public:
        explicit Val(ValType t) : type(t) {}
        virtual ~Val() = default;


        static inline bool classof(const Val *) {return true;}

        ValType getType() const;
        /*virtual bool isTainted(Taint &taint) const = 0;
        virtual bool isTainted(Taint &taint, const TaintLabel &label) const = 0;
        virtual bool addTaint(Taint &taint, const TaintLabel &label) const = 0;
        virtual bool untaint(Taint &taint) const = 0;
        virtual bool untaint(Taint &taint, const TaintLabel &label) const = 0;
        virtual std::vector<TaintLabel *> taintedWith(Taint &taint) const = 0;*/
        virtual std::size_t hash() const = 0;
        virtual bool operator==(const Val &rhs) const = 0;
        /*
         * bool isTainted(const RegisterVal &v) const;
        bool isTainted(const RegisterVal &v, const TaintLabel &label) const;

        bool addTaint(const RegisterVal &v, const TaintLabel &label);
        bool untaint(const RegisterVal &v, const TaintLabel &label);
        bool untaint(const RegisterVal &v);
        std::vector<TaintLabel *> taintedWith(const RegisterVal &v) const;
         uint64_t getTaint(const RegisterVal &v) const;
        bool setTaint(const RegisterVal &v, uint64_t mask);
         */

        // Static Types
        static std::vector<Val *> functionOutputs(const llvm::Function &fn);
        static std::vector<Val *> functionArgs(const llvm::Function &fn);
    protected:
        friend Taint;

        virtual uint64_t getTaint(const Taint &taint) const = 0;
        virtual bool setTaint(Taint &taint, uint64_t mask) const = 0;
        virtual bool addTaint(Taint &taint, uint64_t mask) const = 0;
        virtual bool untaint(Taint &taint, uint64_t mask) const = 0;
    private:
        ValType type;
    };

    struct ValPtrHash {
        std::size_t operator()(const Val *v) const {
            return v->hash();
        }
    };



    struct ValPtrEq {
        bool operator()(const Val *lhs, const Val *rhs) const {
            if(lhs == nullptr && rhs == nullptr) {
                return true;
            }

            if(lhs == nullptr || rhs == nullptr) {
                return false;
            }

            return *lhs == *rhs;
        }
    };
}

#endif //VANGUARD_VAL_H
