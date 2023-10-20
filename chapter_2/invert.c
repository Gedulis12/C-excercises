#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main()
{
    int a = invert(85, 4, 3);
    printf("invert returned: %i \n", a); // should print 73
}

/*
Returns x with the n bits that begin at position p inverted (0 changed to 1 and vice versa), leaving the other bits unchanged.

Example invert(85, 4, 3) should return 01001001 or 227 in decimal:
x = 01010101
~0 = 11111111
~0 << n = 11111000
~(~0 << n) = 00000111
~(~0 << n) << (p+1-n) = 00011100
~x ^ ~(~0 << n) << (p+1-n) = 10101010 ^ 00011100 = 10110110
~(~x ^ ~(~0 << n) << (p+1-n)) = 01001001 or 73 in decimal
*/
unsigned invert(unsigned x, int p, int n)
{
    return ~(~x ^ ~(~0 << n) << (p+1-n));
/*
*/
}
