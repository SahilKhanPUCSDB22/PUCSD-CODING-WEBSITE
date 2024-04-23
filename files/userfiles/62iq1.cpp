#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
    struct LocalVariableCounter : public FunctionPass {
        static char ID;
        LocalVariableCounter() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            int localVarCount = 0;
            for (auto &BB : F) {
                for (auto &Inst : BB) {
                    if (auto *allocaInst = dyn_cast<AllocaInst>(&Inst)) {
                        // Alloca instruction signifies a local variable
                        localVarCount++;
                    }
                }
            }
            errs() << "Function " << F.getName() << " has " << localVarCount << " local variables.\n";
            return false;
        }
    };
}

char LocalVariableCounter::ID = 0;

static RegisterPass<LocalVariableCounter> X("local-var-counter", "Counts local variables in each function");

/*------------------------------------------------------------------------------------------------------------*/

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/CFG.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
    struct LoopAnalysis : public FunctionPass {
        static char ID;
        LoopAnalysis() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            errs() << "Analyzing function: " << F.getName() << "\n";

            for (auto &BB : F) {
                for (auto &Inst : BB) {
                    if (auto *brInst = dyn_cast<BranchInst>(&Inst)) {
                        if (brInst->isConditional()) {
                            if (brInst->getNumSuccessors() == 2) {
                                BasicBlock *trueBB = brInst->getSuccessor(0);
                                BasicBlock *falseBB = brInst->getSuccessor(1);
                                if (trueBB->comesBefore(falseBB)) {
                                    // Back edge found
                                    BasicBlock *loopHeader = falseBB;
                                    errs() << "Loop Header: " << loopHeader->getName() << "\n";
                                    errs() << "Loop Entry: " << BB.getName() << "\n";
                                    errs() << "Back Edge: " << BB.getName() << " -> " << loopHeader->getName() << "\n";
                                    
                                    // Find loop exit conditions
                                    Value *condition = brInst->getCondition();
                                    errs() << "Loop Exit Condition: " << *condition << "\n";

                                    // Calculate loop nesting depth
                                    unsigned int depth = 0;
                                    BasicBlock *currBB = &BB;
                                    while (currBB != loopHeader) {
                                        for (auto &Pred : predecessors(currBB)) {
                                            if (Pred->comesBefore(currBB)) {
                                                currBB = Pred;
                                                depth++;
                                                break;
                                            }
                                        }
                                    }
                                    errs() << "Loop Nesting Depth: " << depth << "\n\n";
                                }
                            }
                        }
                    }
                }
            }

            return false;
        }
    };
}

char LoopAnalysis::ID = 0;

static RegisterPass<LoopAnalysis> X("loop-analysis", "Analyzes loops in LLVM functions");

/*-----------------------------------------------------------------------------------------------------------*/
