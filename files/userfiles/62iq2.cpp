#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/CFG.h"
#include "llvm/Support/raw_ostream.h"
#include <set>
#include <map>

using namespace llvm;

namespace {
    struct LiveVariableAnalysis : public FunctionPass {
        static char ID;
        LiveVariableAnalysis() : FunctionPass(ID) {}

        std::map<BasicBlock*, std::set<Value*>> liveVariables;

        bool runOnFunction(Function &F) override {
            errs() << "Analyzing function: " << F.getName() << "\n";

            for (auto &BB : F) {
                std::set<Value*> liveOut;
                liveVariables[&BB] = liveOut;
            }

            bool changed = true;
            while (changed) {
                changed = false;
                for (auto &BB : F) {
                    std::set<Value*> oldLiveOut = liveVariables[&BB];
                    std::set<Value*> newLiveOut;
                    for (auto *Succ : successors(&BB)) {
                        std::set_union(newLiveOut.begin(), newLiveOut.end(),
                                       liveVariables[Succ].begin(), liveVariables[Succ].end(),
                                       std::inserter(newLiveOut, newLiveOut.begin()));
                    }
                    std::set<Value*> newLiveIn;
                    std::set_difference(newLiveOut.begin(), newLiveOut.end(),
                                        BB.begin(), BB.end(),
                                        std::inserter(newLiveIn, newLiveIn.begin()));
                    liveVariables[&BB] = newLiveIn;
                    if (oldLiveOut != newLiveIn) {
                        changed = true;
                    }
                }
            }

            for (auto &BB : F) {
                errs() << "Basic Block: " << BB.getName() << "\n";
                errs() << "Live Variables: ";
                for (auto *V : liveVariables[&BB]) {
                    errs() << *V << ", ";
                }
                errs() << "\n\n";
            }

            return false;
        }
    };
}

char LiveVariableAnalysis::ID = 0;

static RegisterPass<LiveVariableAnalysis> X("live-variable-analysis", "Performs live variable analysis on LLVM functions");

/*--------------------------------------------------------------------------------------------------------------*/

define i32 @main() {
  %1 = alloca i32             ; in: {}          out: {%1}
  %2 = alloca i32             ; in: {}          out: {%2}
  store i32 10, i32* %1       ; in: {}          out: {%1}
  %3 = load i32, i32* %1      ; in: {%1}        out: {%1, %3}
  %4 = add i32 %3, 5          ; in: {%1, %3}   out: {%1, %3}
  store i32 %4, i32* %2       ; in: {%1, %3}   out: {%1, %4}
  %5 = load i32, i32* %2      ; in: {%1, %4}   out: {%5}
  ret i32 %5                  ; in: {%5}       out: {}
}

/*--------------------------------------------------------------------------------------------------------------*/
