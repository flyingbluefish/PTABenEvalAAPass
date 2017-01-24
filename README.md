PTABenEvalAAPass

This is one of unofficial LLVM Pass which intends to evaluate Alias Analysis (AA) passes performance by compiling PTABen testsuites. 

It is difficult to measure the performance of Alias Analysis pass. Because there is no common method of how to specify the location and result of the alias check result. At least, the method should clear which variables or expressions should be investigated as alias, where the comparison between pointers should be performed, and what alias level is expected between them. So it is hard to develop and accumlate accurate test programs as testing resource. Framework is expected and required for AA pass evaluation. There have been several trials to this problem. Someone tries to add #pragma, someone uses special string.
In this situation, PTABen test suite provides smart solution and be useful to evaluate AA Pass. The testsuites uses MARKER functions to indicate the trigger of checking alias.  

This pass provides an evaluation functionality as checking alias according to MARKER functions specified inside PTABen test suites;

PTABen test program contains the following MARKER functions.
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


Setup
```
llvm-config should be available
```

Build
```
llvm-config
cd $SOMEDIR/PTABenEvalAAPass
mkdir build
cd build
cmake ..
make
```

Usage

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
  pta  (score)  (result MAY|MUST|NO) ex (expected MAY|MUST|NO)  (optional linenumber)
```  
The line is generated when a MARKER function is specified in test program. Every calling of MARKER function generates a line.

For example
```
===== Alias Analysis Benchmark Evaluator Result =====
  pta true MAY ex MAY
  pta true MAY ex MAY
  pta true MAY ex MAY
  pta true MAY ex MAY
  pta inadequate MAY ex NO
```

Score

As score, inadequate, toomuch, true, false, buggy are expected. inadequate means NO or MUST is expected but MAY acquired, toomuch means MAY is expected but MUST, true means the expected result is acquired (MUST expected and MUST acquired, MAY expected and MAY acquired, NO expected and NO acquired), false means MUST or MAY expected but NO, buggy means NO expected but MUST. 

Score is the one of the following:
inadequate, true, false, buggy, toomuch

They comes from the optimization point of view. 



Notice

This software is developped independently. Don't ask question about this software to PTABen author.

Working with LLVM 3.9
