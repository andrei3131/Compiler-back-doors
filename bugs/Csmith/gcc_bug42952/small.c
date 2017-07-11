extern int printf (__const char *__restrict __format, ...);

/* GCC: 4.5.0
The program below looks to me like it should print "0".

regehr@john-home:~$ current-gcc -O small.c -o small
regehr@john-home:~$ ./small
1
*/


// CONCISE VERSION
extern void abort (void);

static int g[1];

static int *p = &g[0];
static int *q = &g[0];

int main(void)
{
  g[0] = 1;
  *p = 0;
  *p = *q;
  printf("%d\n", g[0]);
  if (g[0] != 0)
    abort ();
  return 0;
}


// static int g_16[1];
//
// static int *g_135 = &g_16[0];
// static int *l_15 = &g_16[0];
//
// static void foo (void)
// {
//   g_16[0] = 1;
//   *g_135 = 0;
//   *g_135 = *l_15;
//   printf("%d\n", g_16[0]);
// }
//
// int main(void)
// {
//    foo();
//    return 0;
// }
