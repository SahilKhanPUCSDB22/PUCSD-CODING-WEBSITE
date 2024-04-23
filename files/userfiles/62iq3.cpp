#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/CFG.h"
#include "llvm/Support/raw_ostream.h"
#include <queue>
#include <set>

using namespace llvm;

namespace {
    struct DeadCodeAnalysis : public FunctionPass {
        static char ID;
        DeadCodeAnalysis() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            errs() << "Analyzing function: " << F.getName() << "\n";

            std::set<BasicBlock*> reachableBlocks;
            std::queue<BasicBlock*> worklist;
            BasicBlock &entryBlock = F.getEntryBlock();

            worklist.push(&entryBlock);

            while (!worklist.empty()) {
                BasicBlock *BB = worklist.front();
                worklist.pop();
                reachableBlocks.insert(BB);

                for (BasicBlock *Succ : successors(BB)) {
                    if (reachableBlocks.find(Succ) == reachableBlocks.end()) {
                        worklist.push(Succ);
                    }
                }
            }

            bool modified = false;

            for (BasicBlock &BB : F) {
                if (reachableBlocks.find(&BB) == reachableBlocks.end()) {
                    errs() << "Unreachable code detected in basic block: " << BB.getName() << "\n";
                    // Remove instructions from the unreachable basic block
                    for (Instruction &Inst : BB) {
                        Inst.eraseFromParent();
                    }
                    modified = true;
                }
            }

            return modified;
        }
    };
}

char DeadCodeAnalysis::ID = 0;

static RegisterPass<DeadCodeAnalysis> X("dead-code-analysis", "Performs dead code analysis on LLVM functions");

/*--------------------------------------------------------------------------------------------------------------*/

Original LLVM code

define i32 @main() {
  entry:
    %1 = alloca i32
    %2 = alloca i32
    store i32 10, i32* %1
    %3 = load i32, i32* %1
    %4 = add i32 %3, 5
    store i32 %4, i32* %2
    %5 = load i32, i32* %2
    ret i32 %5
}

Result after dead code analysis pass (unreachable block entry is removed):

define i32 @main() {
  %1 = alloca i32
  %2 = alloca i32
  store i32 10, i32* %1
  %3 = load i32, i32* %1
  %4 = add i32 %3, 5
  store i32 %4, i32* %2
  %5 = load i32, i32* %2
  ret i32 %5
}

As you can see, the entry block becomes unreachable after the ret instruction. Therefore, it should be removed by the dead code analysis pass.
