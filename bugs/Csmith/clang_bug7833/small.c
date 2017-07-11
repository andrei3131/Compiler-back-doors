/*[regehr@babel work000]$ clang -O1 small.c -o small
[regehr@babel work000]$ ./small
-1
[regehr@babel work000]$ clang -O2 small.c -o small
[regehr@babel work000]$ ./small
255
[regehr@babel work000]$ clang -v
clang version 2.8 (trunk 110342)
Target: x86_64-unknown-linux-gnu
Thread model: posix
*/
extern int printf (__const char *__restrict __format, ...);

static int g_16 = -1;
static int g_108;
int *g_107 = &g_108;
static int **g_106 = &g_107;
static int g_252;
static int g_263 = 0x79B6A971L;

int func_2 (int p_4, int p_5, unsigned long p_6)
{
  g_16 = 0;
  **g_106 |= 7L;
  if (!(((&g_16 == 0) & ((7L >= p_4) >= p_6))))
    {
      return p_5;
    }
  return p_6;
}

int main (void)
{
  g_16 = func_2 (-4L, g_16, g_263) | 1;
  *g_107 = (0 != &g_252);
  printf("%d\n", g_16);
  return 0;
}
