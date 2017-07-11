/* GCC: 4.5.0, 4.4, 4.3
I believe the -O1 result is correct.

regehr@john-home:~/volatile/bugs/tmp290/2$ current-gcc -O1 small.c -o small
regehr@john-home:~/volatile/bugs/tmp290/2$ ./small
11
regehr@john-home:~/volatile/bugs/tmp290/2$ current-gcc -O2 small.c -o small
regehr@john-home:~/volatile/bugs/tmp290/2$ ./small
8
regehr@john-home:~/volatile/bugs/tmp290/2$ current-gcc -v

Using built-in specs.
COLLECT_GCC=current-gcc
COLLECT_LTO_WRAPPER=/home/regehr/z/compiler-install/gcc-r157445-install/libexec/gcc/i686-pc-linux-gnu/4.5.0/lto-wrapper
Target: i686-pc-linux-gnu
Configured with: ../configure --with-libelf=/usr/local --enable-lto --prefix=/home/regehr/z/compiler-install/gcc-r157445-install --program-prefix=r157445- --enable-languages=c,c++
Thread model: posix
gcc version 4.5.0 20100314 (experimental) (GCC)

regehr@john-home:~/volatile/bugs/tmp290/2$ cat small.c
*/
extern int printf (__const char *__restrict __format, ...);

int g_3[9][2];
int l_5[7][6];

void func_1 (void);
void func_1 (void)
{
  int i, j;

  for (i = 0; i < 7; i++) {
    for (j = 0; j < 6; j++) {
      l_5[i][j] = 4;
    }
  }

  for (g_3[8][0] = 1; g_3[8][0] < 8; g_3[8][0] += 7) {
    int *l_6 = &g_3[8][0];
    *l_6 = l_5[5][2];
  }

}

int main (void)
{
  func_1 ();
  printf ("%d\n", g_3[8][0]);
  return 0;
}
