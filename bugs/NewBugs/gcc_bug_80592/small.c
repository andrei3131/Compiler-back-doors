#define TU_SIZE_RECOMMENDED     (0x3f << 16)


//Result in binary 	1111110000000000000000
//Result in decimal 	4128768
//Result in hexadecimal 	3f0000

//gcc doesn't seem able to detect the overflow into 44 bits.
//$ ~/gcc/results/bin/gcc -c -O2 -Wall -Wextra -Wstrict-overflow -Wconversion may2b.cc



/*Follow up comment
Confirmed, any of releases I have (4.5.0+) can't catch that.

Just a nit: -Wstrict-overflow needs -fstrict-overflow and the warning has various levels. Anyhow -Wstrict-overflow=5 and -fstrict-overflow does not work.

Btw. -fsanitize=undefined can catch that easily:

$ cat pr80592.c
#define TU_SIZE_RECOMMENDED     (0x3f << 16)

void g( int a)
{
  __builtin_printf ("value: %d\n", a);
}

int main()
{
    int max_tu_symbol = TU_SIZE_RECOMMENDED - 1;

    g(max_tu_symbol << 23);

    return 0;
}

g++ -O2 -fsanitize=undefined pr80592.c && ./a.out
pr80592.c:12:21: runtime error: left shift of 4128767 by 23 places cannot be represented in type 'int'
value: -8388608
*/



/*Another follow up:
clang can detect this but only if max_tu_symbol is made const:

l.c:9:21: warning: signed shift result (0x1F7FFF800000) requires 46 bits to represent, but 'int' only
      has 32 bits [-Wshift-overflow]
    g(max_tu_symbol << 23);
      ~~~~~~~~~~~~~ ^  ~~
*/

extern void g(int);

void f()
{
    int max_tu_symbol = TU_SIZE_RECOMMENDED - 1;

    g(max_tu_symbol << 23);
}
