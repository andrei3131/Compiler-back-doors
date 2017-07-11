/* GCC: 4.5.0
regehr@john-home:~$ current-gcc -O0 small.c -o small -Wall
regehr@john-home:~$ ./small
1
regehr@john-home:~$ current-gcc -O1 small.c -o small -Wall
regehr@john-home:~$ ./small
0
*/

extern int printf (__const char *__restrict __format, ...);

static unsigned char g_2 = 1;
static int g_9;
static int *l_8 = &g_9;

static void func_12(int p_13)
{
  int * l_17 = &g_9;
  *l_17 &= 0 < p_13;
}

int main(void)
{
  unsigned char l_11 = 254;
  *l_8 |= g_2;
  l_11 |= *l_8;
  func_12(l_11);
  printf("%d\n", g_9);
  return 0;
}
