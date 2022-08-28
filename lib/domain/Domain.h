#ifndef VANGUARD_DOMAIN_DOMAIN_H
#define VANGUARD_DOMAIN_DOMAIN_H

#include <list>
#include "../program/Instruction.h"
#include "../program/Value.h" // TODO: confirm with Jon that this suffices for valueish
#include "../program/InstructionClasses.h" // NOTE: file DNE but possesses callInstruction type
#include "CallEdge.h" 
#include "Context.h"

namespace vanguard {
    class Domain {
        public:
            /*
             * methods for functions that have control dependencies 
            */
            virtual bool resolvesCalls() = 0; 

            virtual std::list<CallEdge*> getCallees(Context context, CallInstruction ins) = 0;

            // Eventually we might want to add this functionality, but if it is added getCallers will take in a Function rather than a callInstruction
            // virtual std::list<CallEdge*> getCallers(Context context, callInstruction instruction) = 0;

            /*
             * methods for functions that have data dependencies
            */
            virtual bool hasAdditionalStorage() = 0;

            // is valueish just a Value? 
            virtual std::list<Value*> getAdditionalStorage() = 0;

            virtual bool readsStorage(Instruction& ins) = 0;

            virtual bool writesStorage(Instruction& ins) = 0;

            virtual std::list<Value*> getStorageReads(Instruction& ins) = 0;

            virtual std::list<Value*> getStorageWrites(Instruction& ins) = 0;
    };
}

#endif 
