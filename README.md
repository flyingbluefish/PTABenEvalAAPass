PTABenEvalAAPass



PTABen test suite is useful in order to evaluate AA Pass. 
This pass provides an evaluation functionality after AA passes 
by checking alias according to intrinsic functions inside PTABen test suites;

- NOALIAS
- MUSTALIAS
- MAYALIAS
- PARTIALALIAS ( not supported yet )

In detail, see PTABen: https://github.com/unsw-corg/PTABen

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

This software is developped independently. Don't ask question about this software to PTABen author.
