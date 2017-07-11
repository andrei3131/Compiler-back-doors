#include <stdint.h>
#include <stdio.h>

/* NOTE: see added patch in attachments
Seen on Ubuntu 9.10.  I think "1" is the right answer.

regehr@john-home:~/volatile/bugs/tmp254$ current-gcc -O1 small.c -o small
regehr@john-home:~/volatile/bugs/tmp254$ ./small
checksum = 1
regehr@john-home:~/volatile/bugs/tmp254$ current-gcc -O2 small.c -o small
regehr@john-home:~/volatile/bugs/tmp254$ ./small
checksum = 0
regehr@john-home:~/volatile/bugs/tmp254$ current-gcc -v
Using built-in specs.
COLLECT_GCC=current-gcc
COLLECT_LTO_WRAPPER=/home/regehr/z/tmp/gcc-r155838-install/libexec/gcc/i686-pc-linux-gnu/4.5.0/lto-wrapper
Target: i686-pc-linux-gnu
Configured with: ../configure --with-libelf=/usr/local --enable-lto --prefix=/home/regehr/z/tmp/gcc-r155838-install --program-prefix=r155838- --enable-languages=c,c++
Thread model: posix
gcc version 4.5.0 20100112 (experimental) (GCC)
*/


static uint64_t safe_div_uint64_t (uint64_t ui1, uint64_t ui2)
{
  return (ui2 == 0) ? ui1 : (ui1 / ui2);
}

static int8_t safe_mod_int8_t (int8_t si1, int8_t si2)
{
  return
    ((si2 == 0) || ((si1 == INT8_MIN) && (si2 == (-1)))) ?
    si1 :
    (si1 % si2);
}

static int32_t g_5;
static int32_t g_11;

int main (void)
{
  uint64_t l_7 = 0x509CB0BEFCDF11BBLL;
  g_11 ^= l_7 && ((safe_div_uint64_t ((safe_mod_int8_t (g_5, 0)), -1L)) != 1L);
  printf ("checksum = %d\n", g_11);
  return 0;
}
