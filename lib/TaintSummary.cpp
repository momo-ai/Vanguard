//
// Created by Jon Stephens on 3/29/22.
//

#include <iostream>
#include "TaintSummary.h"
#include "ReadWriteRetriever.h"
#include "llvm/IR/CFG.h"

namespace vanguard {
    TaintSummary::TaintSummary(const Function &summaryFn, ReadWriteRetriever &rw, const std::vector<FunctionTaintSink *> &sinks, const std::vector<FunctionTaintSource *> &sources, llvm::AAResults *aa) : fn(summaryFn), rwRetriever(rw), alias(aa) {
        initState = new Taint(labelStore, regTaint, alias);
        summary = initState;
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
                    std::vector<TaintLabel *> labels = getOrCreateTaintLabels(initState, taintedVals);
                    for(auto l : labels) {
                        l->addSource(src);
                    }

                }
            }
        }

        bbInit[&fn.getEntryBlock()] = initState;
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
        //ins.print(errs());
        Taint *prev = getPrevTaint(ins);
        ReadWriteInfo info = rwRetriever.retrieve(ins);
        Taint *cur = insToTaint[&ins];
        if(cur == nullptr) {
            cur = new Taint(*prev);
            insToTaint[&ins] = cur;
        }

        bool modified = cur->propagate(*prev, info.reads, info.writes);
        return modified;
    }

    std::vector<TaintLabel *>TaintSummary::getOrCreateTaintLabels(Taint *state, std::vector<Val *> &vals) {
        std::vector<TaintLabel *> labels;
        if(vals.empty()) {
            return labels;
        }

        for(Val *v : vals) {
            /*if(v->type() != ValType::REG_VAL) {
                throw std::runtime_error("Only reg values supported right now");
            }

            RegisterVal *rv = static_cast<RegisterVal *>(v);
            RegisterVal *rv = cast<RegisterVal>(v);*/
            auto valIt = valToLabel.find(v);
            if(valIt == valToLabel.end()) {
                auto l = labelStore.newLabel();
                valToLabel[v] = l;
                state->addTaint(*v, *l);
                labels.push_back(l);
            }
            else {
                labels.push_back(valToLabel.at(v));
            }
        }

        return labels;
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