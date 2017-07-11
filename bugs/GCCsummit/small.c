/*GCC r164319 at -O2 on x86-64 prints “0”*/

#include <stdio.h>

static int x;
static int *volatile z = &x;
static int foo (int *y) {
return *y;
}
int main (void) {
*z = 1;
printf ("%d\n", foo(&x));
return 0;
}
