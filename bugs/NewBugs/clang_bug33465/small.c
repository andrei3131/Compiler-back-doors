//
// Created by andrei-octavian on 21.06.2017.
//

/*
The bug was reported for clang-5.0

Left part of the '||' operator in an assign statement is executed but the right part is not executed.
This will lead the assign statement being marked as unexecuted in the llvm-cov.

$ clang-5.0 -O0 -fcoverage-mapping -fprofile-instr-generate=small.profraw small.c -o small
$ llvm-profdata-5.0 merge -o small.profdata small.profraw
$ llvm-cov-5.0 show small -instr-profile=small.profdata small.c > small.gcov
 */
#include <stdio.h>

int foo(int v)
{
  printf("%s\n", "NEVER");
  return !v;
}

int main()
{
    int g = 0;
    int v = 1;
    g = foo(v) || v; // it actually is executed but the problem is with gcov
    printf("g = %d\n", g); // g's value printed correctly
    return 0;
}
