// PTABenEvalAAPass for 3.9
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"


#include <stdio.h>

using namespace llvm;

namespace {
struct PTABenEvalAAPass : public FunctionPass {
static char ID;
    
  llvm::StringRef NOALIAS;
  llvm::StringRef MAYALIAS;
  llvm::StringRef MUSTALIAS;
  llvm::StringRef PARTIALALIAS;
  llvm::StringRef EXPECTEDFAIL_MAYALIAS;
  llvm::StringRef EXPECTEDFAIL_NOALIAS;
  PTABenEvalAAPass() : FunctionPass(ID), 
		       NOALIAS("NOALIAS"), 
		       MAYALIAS("MAYALIAS"), 
 		       MUSTALIAS("MUSTALIAS"),
		       PARTIALALIAS("PARTIALALIAS"),
		       EXPECTEDFAIL_MAYALIAS("EXPECTEDFAIL_MAYALIAS"),
		       EXPECTEDFAIL_NOALIAS("EXPECTEDFAIL_NOALIAS")
  {
    count = 0;
  }
  virtual void getAnalysisUsage(AnalysisUsage &AU) const ;
  int count;
  virtual bool runOnFunction(Function &F) {
    if (count == 0) printf("===== Alias Analysis Benchmark Evaluator Result =====\n");
    count++;
      //    errs() << "I saw a function called " << F.getName() << "!\n";
    AliasAnalysis *AA = &this->getAnalysis<AAResultsWrapperPass>().getAAResults();  
    const char *ex, *s, *score;

    for (auto &BB : F) {
      for (auto &I : BB) {
	CallInst *call = dyn_cast<CallInst>(&I);
	if (call) {
          const Value *v = call->getCalledFunction();
          if (v == NULL) continue;
          const Function *called = dyn_cast<Function>(v);
          const StringRef &fun = called->getName();
          if (call->getNumArgOperands() != 2) continue;
	  Value* V1 = call->getArgOperand(0);
	  Value* V2 = call->getArgOperand(1);
	  AliasResult aares = AA->alias(V1, V2);
	  bool r = false;
	  if (fun.equals(NOALIAS)) {
            r = (aares == NoAlias); ex = "NO";
            if (aares == NoAlias)
              score = "true";
 	    else if (aares == MayAlias)
              score = "inadequate";
	    else if (aares == MustAlias)
              score = "false";
            else
              score = "inadequate";
	  } else if (fun.equals(MAYALIAS)) {
	    r = (aares == MayAlias || aares == MustAlias); ex = "MAY";
            if (aares == NoAlias)
              score = "false";
 	    else if (aares == MayAlias)
              score = "enough";
	    else if (aares == MustAlias)
              score = "true";
            else
              score = "inadequate";
	  } else if (fun.equals(MUSTALIAS)) {
	    r = (aares == MustAlias); ex = "MUST";
            if (aares == NoAlias)
              score = "false";
 	    else if (aares == MayAlias)
              score = "inadequate";
	    else if (aares == MustAlias)
              score = "true";
            else
              score = "inadequate";
	  } else if (fun.equals(PARTIALALIAS)) {
	    r = (aares == MayAlias || aares == MustAlias); ex = "MAY";
            if (aares == NoAlias)
              score = "false";
 	    else if (aares == MayAlias)
              score = "enough";
	    else if (aares == MustAlias)
              score = "true";
            else
              score = "inadequate";
	  } else if (fun.equals(EXPECTEDFAIL_MAYALIAS)) {
	    r = (aares != MayAlias && r != MustAlias); ex = "EXPECTEDFAIL_MAY";
            if (aares == NoAlias)
              score = "true";
 	    else if (aares == MayAlias)
              score = "false";
	    else if (aares == MustAlias)
              score = "false";
            else
              score = "inadequate";
	  } else if (fun.equals(EXPECTEDFAIL_NOALIAS)) {
	    r = (aares != NoAlias); ex = "EXPECTEDFAIL_NO";
            if (aares == NoAlias)
              score = "false";
 	    else if (aares == MayAlias)
              score = "enough";
	    else if (aares == MustAlias)
              score = "true";
            else
              score = "inadequate";
          } else {
            continue;
	  }
	  if (aares == NoAlias) s = "NO";
	  else if (aares == MayAlias) s = "MAY";
	  else if (aares == MustAlias) s = "MUST";
          else s = "UNKNOWN";
          if (r)
            printf("  pta %s %s ex %s ", score, s, ex);
          else
            printf("  pta %s %s ex %s ", score, s, ex);
          const llvm::DebugLoc &dg = I.getDebugLoc();
          if (dg)
            printf(" %d\n", dg.getLine());
          else
            printf("\n");
	}
      }
    }
    return false;
  }
};
}


void PTABenEvalAAPass::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.addRequired<llvm::AAResultsWrapperPass>();
  //  AU.addRequired<llvm::MemoryDependenceWrapperPass>();
  //  AU.addRequired<llvm::DependenceAnalysisWrapperPass>();
}

char PTABenEvalAAPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
//static void registerPTABenEvalAAPass(const PassManagerBuilder &,
//				     legacy::PassManagerBase &PM) {
//  PM.add(new PTABenEvalAAPass());
//}
//static RegisterStandardPasses
//RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
//	       registerPTABenEvalAAPass);

static RegisterPass<PTABenEvalAAPass>
XF("aa-eval-ptaben", "Alias Analysis presision evaluator using PTABen", false, false);
