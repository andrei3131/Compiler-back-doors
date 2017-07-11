/*regehr@john-home:~/work013$ clang -O0 small.c -o small
regehr@john-home:~/work013$ ./small
1
regehr@john-home:~/work013$ clang -O2 small.c -o small
regehr@john-home:~/work013$ ./small
0

regehr@john-home:~/work013$ clang -v

clang version 2.8 (trunk 109491)
Target: i386-pc-linux-gnu
Thread model: posix
*/

static short foo (short left, unsigned int right)
{
  return left;
}

struct S0
{
  unsigned f7:15;
};

unsigned short g_158[8] = {
  0xAF2FL, 0xAF2FL, 0xAF2FL, 0xAF2FL, 0xAF2FL, 0xAF2FL, 0xAF2FL, 0xAF2FL
};

struct S0 g_556[9][2];

struct S0 g_558 = {
  0L
};

unsigned char l_565[3][1];

extern int printf (__const char *__restrict __format, ...);

int main (void)
{
  const int g_264 = 1L;
  struct S0 *l_555 = &g_556[4][0];
  struct S0 *l_557 = &g_558;
  short y = foo ((l_555 == l_557) | (g_264 && g_158[2]), 0);
  printf ("%d\n", g_264 == y);
  return 0;
}
