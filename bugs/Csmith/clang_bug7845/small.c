/*[regehr@babel work001]$ clang -O1 small.c -o small
[regehr@babel work001]$ ./small
5
[regehr@babel work001]$ clang -O2 small.c -o small
[regehr@babel work001]$ ./small
1
[regehr@babel work001]$ clang -v
clang version 2.8 (trunk 110555)
Target: x86_64-unknown-linux-gnu
Thread model: posix
*/
extern int printf (__const char *__restrict __format, ...);

short foo (int left)
{
  return left;
}

int main(void)
{
  int g_4;
  for (g_4 = 0; g_4 < 5; g_4 += 1)
    {
      int l_9 = foo (g_4);
      if (l_9) continue;
      if (g_4) break;
    }
  printf("%d\n", g_4);
  return 0;
}
