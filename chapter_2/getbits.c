#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);

int main ()
{
    int a = getbits(85, 4, 3);
    printf("getbits returned: %i \n", a); // should print 5
}

/*
The x >> (p+1-n) moves the desired field to the right end of the word.
~0 is all 1-bits.
shifting it left n positions with ~0 <<n places zeros in the rightmost n bits.
complementing that with ~ makes a mask with ones in the rightmost n bits.

Example:
getbits(85, 4, 3) should return 101 at the end of 8bit field 00000101 or 5 in decimal representation
x = x7 x6 x5 x4 x3 x2 x1 x0
x =  0  1  0  1  0  1  0  1
 (p + 1 - n) = 4 + 1 - 3 = 2
 x >> 2      = 00010101
 ~0          = 11111111
 ~0 << n     = ~0 << 3
 ~0 << n     = 11111000
 ~(~0 << n)  = 00000111
 00010101 & 00000111 = 00000101

*/
unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);

}
