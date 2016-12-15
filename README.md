PTABenEvalAAPass

This is one of unofficial LLVM Pass which evaluates Alias Analysis (AA) passes performance by compiling PTABen testsuites. 

PTABen test suite is useful in order to evaluate AA Pass. 
This pass provides an evaluation functionality after AA passes 
by checking alias according to intrinsic functions inside PTABen test suites;

- NOALIAS
- MUSTALIAS
- MAYALIAS
- PARTIALALIAS ( not supported yet )
- EXPECTEDFAIL_NOALIAS
- EXPECTEDFAIL_MAYALIAS

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
