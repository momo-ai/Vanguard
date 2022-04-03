//
// Created by Jon Stephens on 3/29/22.
//

#include <iostream>
#include "TaintSummary.h"
#include "ReadWriteRetriever.h"
#include "llvm/IR/CFG.h"
#include "TaintSummaryStore.h"
#include "Val.h"

namespace vanguard {
    TaintSummary::TaintSummary(TaintSummaryStore &parent, Function &summaryFn, ReadWriteRetriever &rw, const std::vector<FunctionTaintSink *> &sinks, const std::vector<FunctionTaintSource *> &sources, llvm::Pass &pass) : store(parent), labelStore(*this), fn(summaryFn), rwRetriever(rw), alias(pass, summaryFn) {
        initState = new Taint(labelStore, regTaint, alias);
        summary = new Taint(labelStore, regTaint, alias);
        for(auto sink : sinks) {
            if(sink->isSink(summaryFn)) {
                sink->registerProvider(this);
            }
        }

        for(auto src : sources) {
            if(src->isSource(summaryFn)) {
                std::vector<Val *> taintedVals = src->sourceValues(fn);
                if(!taintedVals.empty()) {
                    /*TODO: can probably consolidate some of these labels*/
                    fnSources.push_back(src);
                    std::vector<TaintLabel *> labels = initState->getOrCreateTaintLabels(taintedVals);
                    for(auto l : labels) {
                        l->addSource(src);
                    }

                }
            }
        }

        bbInit[&fn.getEntryBlock()] = initState;
    }

    const TaintSummaryStore &TaintSummary::parent() {
        return store;
    }

    const Function &TaintSummary::function() const {
        return fn;
    }

    AAWrapper &TaintSummary::getAliasWrapper() {
        return alias;
    }

    TaintSummary::~TaintSummary() {
        delete initState;

        for(auto entry : insToTaint) {
            delete entry.second;
        }

        insToTaint.clear();
    }

    Taint *TaintSummary::getPrevTaint(const llvm::Instruction &ins) {
        const Instruction *prev = ins.getPrevNode();

        if(prev != nullptr) {
            return insToTaint.at(prev);
        }

        std::vector<Taint *> toMerge;
        const BasicBlock *blk = ins.getParent();
        for(auto pred : predecessors(blk)) {
            const Instruction *term = pred->getTerminator();
            Taint *t = insToTaint[term];
            if(t != nullptr) {
                toMerge.push_back(t);
            }
        }

        Taint *blkTaint = bbInit[blk];
        if(blkTaint == nullptr) {
            blkTaint = new Taint(labelStore, regTaint, alias);
            bbInit[blk] = blkTaint;
        }

        blkTaint->merge(toMerge);
        return blkTaint;
    }

    bool TaintSummary::propagate(const llvm::Instruction &ins) {
        if(auto call = dyn_cast<const llvm::CallInst>(&ins)) {
            return propagate(*call);
        }
        //ins.print(outs());
        //std::cout << std::endl;
        Taint *prev = getPrevTaint(ins);
        ReadWriteInfo info = rwRetriever.retrieve(ins);
        Taint *cur = insToTaint[&ins];
        if(cur == nullptr) {
            cur = new Taint(*prev);
            insToTaint[&ins] = cur;
        }

        bool modified = cur->propagate(*prev, info.reads, info.writes);
        return modified || info.requiresUpdate;
    }

    bool TaintSummary::propagate(const llvm::CallInst &call) {
        std::cout << "  called: " << call.getCalledFunction()->getName().str() << std::endl;
        bool requiresUpdate = false;
        std::unordered_map<Val *, Val *, ValPtrHash, ValPtrEq> inVals = Val::inVals(call);
        std::unordered_map<Val *, Val *, ValPtrHash, ValPtrEq> outVals = Val::outVals(call);

        TaintSummary *callee = store.getSummary(*call.getCalledFunction());
        Taint *prev = getPrevTaint(call);
        Taint *cur = insToTaint[&call];
        if(cur == nullptr) {
            cur = new Taint(*prev);
            insToTaint[&call] = cur;
        }

        //std::vector<TaintLabel *> calleeTaint;
        //std::unordered_map<TaintLabel *, std::vector<TaintLabel *>> calleeToCaller;
        for(auto &entry : inVals) {
            Val *callerVal = entry.first;
            Val *calleeVal = entry.second;

            if(!cur->isTainted(*callerVal)) {
                continue;
            }

            if(!callee->initState->hasValLabel(*calleeVal)) {
                requiresUpdate = true;
            }

            // Get the taint label
            TaintLabel *calleeLabel = callee->initState->getOrCreateTaintLabel(*calleeVal);

            //connect taint labels
            for(TaintLabel *callerLabel : cur->taintedWith(*callerVal)) {
                calleeLabel->addNode(callerLabel);
                //calleeToCaller[calleeLabel].push_back(callerLabel);
            }

            //delete callerVal;
            //delete calleeVal;
        }

        for(auto &entry : outVals) {
            Val *calleeVal = entry.first;
            Val *callerVal = entry.second;

            if(!callee->summary->isTainted(*calleeVal)) {
                continue;
            }

            TaintLabel *callerLabel = cur->getOrCreateTaintLabel(*callerVal);

            for(TaintLabel *calleeLabel : callee->summary->taintedWith(*calleeVal)) {
                callerLabel->addNode(calleeLabel);
            }

            //delete calleeVal;
            //delete callerVal;
        }

        //see if any of our taint labels

        return requiresUpdate;
    }

    std::vector<TaintNode *> TaintSummary::getTaint(FunctionTaintSink &sink) {
        std::vector<TaintNode *> labels;
        if(!sink.isSink(fn)) {
            return labels;
        }

        std::vector<Val *> sinkVals = sink.sinkValues(fn);
        for(auto &val : sinkVals) {
            for(TaintLabel *l : summary->taintedWith(*val)) {
                labels.push_back(l);
            }
        }

        return labels;
    }

    bool TaintSummary::didSummaryChange() {
        return computeSummary();
    }

    bool TaintSummary::computeSummary() {
        std::vector<Taint *> finalStates;

        for(auto &blk : fn) {
            if(successors(&blk).empty()) {
                auto termIns = blk.getTerminator();
                if(insToTaint.find(termIns) != insToTaint.end()) {
                    finalStates.push_back(insToTaint.at(termIns));
                }
            }
        }

        if(finalStates.empty()) {
            summary = initState;
            return false;
        }

        bool updated = false;
        if(summary == initState) {
            summary = new Taint(labelStore, regTaint, alias);
            updated = true;
        }

        updated = summary->merge(finalStates) || updated;

        return updated;
    }

    /*void TaintSummary::checkSinks() {
        for(auto sink : fnSinks) {
            if(!sink->isSink(fn)) {
                continue;
            }

            std::vector<Val *> sinkVals = sink->sinkValues(fn);

            for(auto &val : sinkVals) {
                for(TaintLabel *l : initState->taintedWith(*val)) {
                    sink->addTaint(l);
                }
            }
        }
    }*/

    /*bool computeFinalState() {

    }*/
}