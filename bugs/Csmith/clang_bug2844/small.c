/*
This is seen on r56829 on Ubuntu Hardy on ia32.  llvm-gcc is valgrind-clean at both optimization levels.  0 is the right answer I believe.

regehr@john-home:~/volatile/tmp49$ llvm-gcc -O1 small.c -o small
regehr@john-home:~/volatile/tmp49$ ./small
0
regehr@john-home:~/volatile/tmp49$ llvm-gcc -O2 small.c -o small
regehr@john-home:~/volatile/tmp49$ ./small
1
*/
#include <stdio.h>

static inline unsigned long int
mod_rhs(const long int rhs)
{
    if (rhs == 0) return 1;
    return rhs;
}

static inline unsigned long int
div_rhs(const long int rhs)
{
    if (rhs == 0) return 1;
    return rhs;
}

static inline unsigned int
rshift_u_u(unsigned int left, unsigned int right)
{
	if (right >= sizeof(unsigned int)*8) {
		return left;
	}
	return left >> right;
}

unsigned int g_52;
unsigned int g_241;
unsigned int g_247;
unsigned int g_253;

int func_8 (unsigned int p_10);
int func_8 (unsigned int p_10)
{
  unsigned int l_11 = 0;
  for (1; l_11; l_11 -= 1)
    {
    }
  return 1;
}

int func_65 (unsigned short p_67, int p_69);
int func_65 (unsigned short p_67, int p_69)
{
  unsigned int l_70 = 0xD9F5B60AL;
  return l_70;
}

int func_76 (signed char p_78);
int func_76 (signed char p_78)
{
  p_78 = 1 % mod_rhs (1);
  return 1;
}

int func_73 (int p_74);
int func_73 (int p_74)
{
  unsigned int l_75 = 1;
  unsigned int l_77 = 1;
  unsigned int l_264 = 0;
  func_65 (((rshift_u_u
	     (l_75,
	      (func_76 (p_74)
	       || l_75 + func_8 (1)) <= 1 & 1 < (g_241 ^ (1 ==
							  p_74)) *
	      (func_65 ((g_247 * l_77), 1)
	       && (g_241 & (1 >= l_77))))) - 1), p_74 && ((g_52 | l_77)
							  && l_75
							  && (1 /
							      div_rhs (1))) *
	   ((p_74 ^ (func_8 (1) != (1 % mod_rhs (1)))) <= 1) - (1 >= l_264));
  g_253 = (p_74 && (p_74 > func_65 (0x76L, 1)));
  return 1;
}

int main (void)
{
  func_73 (0);
  printf ("%d\n", g_253);
  return 0;
}
