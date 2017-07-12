#include <stdio.h>

__attribute__ ((noinline))
foo(short unsigned int *p1, short unsigned int *p2)
{
  short unsigned int x1, x4;
  printf("The size of short unsigned int is %d bytes\n", sizeof(short unsigned int));
  printf("The size of unsigned int is %d bytes\n", sizeof(unsigned int));
  int x2, x3, x5, x6;
  unsigned int x7;
  
  x1 = *p1;
  x2 = (int) x1;  // The cast zero-extends 0xfffb
  printf("x2 = 0x%.8x\n", x2);  // x2 = 65531
  x3 = x2 * 65536;
  x4 = *p2;
  x5 = (int) x4;
  x6 = x3 + x4;
  x7 = (unsigned int) x6; 
  printf("(int) x6 = 0x%.8x and %d\n", x6, x6); 
  // x6 = 0xfffbfff6; in decimal -262154
  printf("(unsigned int) x7 = 0x%.8x and %u\n", x7, x7);
  // x7 = 0xfffbfff6; in decimal 4294705142
 
  // C unsigned comparison: if one operand is unsigned, the other operand is 
  // converted to unsigned, making, for example, -1 > 2U true.
  if (x7 <= 268435455U)
     abort ();
  exit (0);
}

main()
{
  short unsigned int x, y;
  x = -5;
  y = -10;
  // x = 0x0000fffb and y = 0x0000fff6
  printf("x = 0x%.8x and y = 0x%.8x\n", x, y);
  foo (&x, &y);
}
