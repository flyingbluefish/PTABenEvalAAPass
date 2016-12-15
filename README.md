PTABenEvalAAPass

This is one of unofficial LLVM Pass which intends to evaluate Alias Analysis (AA) passes performance by compiling PTABen testsuites. 

PTABen test suite is useful in order to evaluate AA Pass. 
This pass provides an evaluation functionality after AA passes 
by checking alias according to intrinsic MARKER functions inside PTABen test suites;

PTABen test program contains following MARKER function.
- NOALIAS
- MUSTALIAS
- MAYALIAS
- PARTIALALIAS ( not supported yet )
- EXPECTEDFAIL_NOALIAS
- EXPECTEDFAIL_MAYALIAS

This pass recognises the above MARKER functions in IR and then tries to check alias of the arguments of these functions
by passing the internal representaion as LLVM IR objects to Alias Analysis of LLVM infrastructure.
Each AAes are registered before executing this pass, so the alias checking will measure the integrated performance of each AAes.

About test suite itself in detail, see PTABen: https://github.com/unsw-corg/PTABen



To get .ll by compiling an PTABen test
```
clang -emit-llvm -S some.c
```

When using this pass, the followin' options are specified on the command line of opt command.

```
opt -load $SOMEDIR/PTABenEvalAAPass/build/lib/libptabenevalaa.so -aa-eval-ptaben some.ll
```

Expected result is like following

A line shows
```
  pta  (true or false)  (result MAY|MUST|NO) ex (expected MAY|MUST|NO)  (optional linenumber)
```  

For example
```
===== Alias Analysis Benchmark Evaluator Result =====
  pta true MAY ex MAY
  pta true MAY ex MAY
  pta true MAY ex MAY
  pta true MAY ex MAY
  pta false MAY ex NO
```

inadequate, enough, good, true, false are expected. inadequate means no or must is expected but may, enough means may is expected then may, good means may is expected but no or must, true means expected result is acquired, false means might-be-runtime-error. 




This software is developped independently. Don't ask question about this software to PTABen author.
