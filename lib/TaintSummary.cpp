//
// Created by Jon Stephens on 3/29/22.
//

#include <iostream>
#include "TaintSummary.h"
#include "ReadWriteRetriever.h"
#include "llvm/IR/CFG.h"
#include "TaintSummaryStore.h"
#include "Val.h"

using namespace std;
using namespace blockchain;

namespace vanguard {
    TaintSummary::TaintSummary(TaintSummaryStore &parent, Function &summaryFn, ReadWriteRetriever &rw, const vector<FunctionTaintSink *> &sinks, const vector<FunctionTaintSource *> &sources, AAWrapper &alias) : store(parent), labelStore(*this), fn(summaryFn), rwRetriever(rw), alias(alias) {
        initState = new Taint(summaryFn, labelStore, regTaint, alias);
        summary = new Taint(summaryFn, labelStore, regTaint, alias);
        for(auto sink : sinks) {
            if(sink->isSink(summaryFn)) {
                sink->registerProvider(this);
            }
        }

        for(auto src : sources) {
            if(src->isSource(summaryFn)) {
                vector<pair<FunctionLocation, Val *>> taintedVals = src->sourceValues(fn);
                if(!taintedVals.empty()) {
                    fnSources.push_back(src);
                    vector<TaintLabel *> labels = getOrCreateTaintLabels(taintedVals);
                    for(auto l : labels) {
                        l->addSource(src);
                        generatedLabels.insert(l);
                    }

                }
            }
        }

        bbInit[&fn.getEntryBlock()] = initState;
    }

    vector<TaintLabel *> TaintSummary::getOrCreateTaintLabels(std::vector<std::pair<FunctionLocation, Val *>> &vals) {
        vector<TaintLabel *> labels;
        for(auto &entry : vals) {
            if(entry.first == INPUT) {
                labels.push_back(initState->getOrCreateTaintLabel(*entry.second));
            }
            else {
                labels.push_back(summary->getOrCreateTaintLabel(*entry.second));
            }
        }

        return labels;
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

    bool TaintSummary::isGenerated(const TaintLabel *label) const {
        return generatedLabels.find(label) != generatedLabels.end();
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
            blkTaint = new Taint(fn, labelStore, regTaint, alias);
            bbInit[blk] = blkTaint;
        }

        blkTaint->merge(toMerge);
        return blkTaint;
    }

    bool TaintSummary::propagate(const llvm::Instruction &ins) {
        //ins.print(outs());
        //std::cout << std::endl;
        if(auto call = dyn_cast<const llvm::CallInst>(&ins)) {
            return propagate(*call);
        }

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
        //string calledFnName = call.getCalledFunction()->getName().str();
        //std::cout << "  called: " << calledFnName << std::endl;
        bool requiresUpdate = false;
        std::unordered_map<Val *, Val *, ValPtrHash, ValPtrEq> inVals = Val::inVals(call);
        std::unordered_map<Val *, Val *, ValPtrHash, ValPtrEq> outVals = Val::outVals(call);

        //can't resolve target. Assume that it doesn't do anything for now.
        if(call.getCalledFunction() == nullptr) {
            Taint *prev = getPrevTaint(call);
            Taint *cur = insToTaint[&call];
            if(cur == nullptr) {
                cur = new Taint(*prev);
                insToTaint[&call] = cur;
            }
            return false;
        }

        TaintSummary *callee = store.getSummary(*call.getCalledFunction());
        Taint *prev = getPrevTaint(call);
        Taint *cur = insToTaint[&call];
        if(cur == nullptr) {
            cur = new Taint(*prev);
            insToTaint[&call] = cur;
        }

        //std::vector<TaintLabel *> calleeTaint;
        //std::unordered_map<TaintLabel *, std::vector<TaintLabel *>> calleeToCaller;
        //interesting labels are those that pass through + any that are generated in callee
        std::unordered_set<const TaintLabel *> passThroughLabels;
        std::unordered_set<const TaintLabel *> passThroughGenLabels;
        for(auto &entry : inVals) {
            Val *callerVal = entry.first;
            Val *calleeVal = entry.second;

            if(!prev->isTainted(*callerVal)) {
                continue;
            }

            if(!callee->initState->hasValLabel(*calleeVal)) {
                requiresUpdate = true;
            }

            // Get the taint label
            TaintLabel *calleeLabel = callee->initState->getOrCreateTaintLabel(*calleeVal);
            passThroughLabels.insert(calleeLabel);

            //connect taint labels
            for(TaintLabel *callerLabel : prev->taintedWith(*callerVal)) {
                if(generatedLabels.find(callerLabel) != generatedLabels.end()) {
                    passThroughGenLabels.insert(calleeLabel);
                }

                calleeLabel->addNode(callerLabel);
                //calleeToCaller[calleeLabel].push_back(callerLabel);
            }

            //delete callerVal;
            //delete calleeVal;
        }

        for(auto &entry : outVals) {
            Val *calleeVal = entry.first;
            Val *callerVal = entry.second;

            if(callee->summary->isTaintedWith(*calleeVal, callee->generatedLabels)) {
                TaintLabel *callerLabel = cur->getOrCreateTaintLabel(*callerVal);
                generatedLabels.insert(callerLabel);

                for(TaintLabel *calleeLabel : callee->summary->taintedWith(*calleeVal)) {
                    if(passThroughLabels.find(calleeLabel) != passThroughLabels.end() || callee->generatedLabels.find(calleeLabel) != callee->generatedLabels.end()) {
                        callerLabel->addNode(calleeLabel);
                    }
                }
            }
            else if(callee->summary->isTaintedWith(*calleeVal, passThroughLabels)) {
                TaintLabel *callerLabel = cur->getOrCreateTaintLabel(*callerVal);

                for(TaintLabel *calleeLabel : callee->summary->taintedWith(*calleeVal)) {
                    if(passThroughLabels.find(calleeLabel) != passThroughLabels.end() || callee->generatedLabels.find(calleeLabel) != callee->generatedLabels.end()) {
                        if(passThroughGenLabels.find(calleeLabel) != passThroughGenLabels.end()) {
                            generatedLabels.insert(callerLabel);
                        }

                        callerLabel->addNode(calleeLabel);
                    }
                }
            }

            //delete calleeVal;
            //delete callerVal;
        }

        //see if any of our taint labels

        return requiresUpdate;
    }

    std::vector<TaintNode *> TaintSummary::getTaint(const FunctionTaintSink &sink) const {
        std::vector<TaintNode *> labels;
        if(!sink.isSink(fn)) {
            return labels;
        }

        vector<pair<FunctionLocation, Val *>> sinkVals = sink.sinkValues(fn);
        for(auto &entry : sinkVals) {
            Taint *checkTaint = summary;
            if(entry.first == INPUT) {
                checkTaint = initState;
            }
            for(TaintLabel *l : checkTaint->taintedWith(*entry.second)) {
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
            return false;
        }

        bool updated = false;
        if(summary == initState) {
            summary = new Taint(fn, labelStore, regTaint, alias);
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