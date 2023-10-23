#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main()
{
    int a = rightrot(85, 11);
    printf("rightrot returned: %i \n", a); // should print 170
}


/*
returns the value of the integer x rotated to the right by n positions.

Example rightrot(85, 11); should return 101001010 or 170 in decimal:
x = 01010101
x & ~(~0 << n) = 01010101 & 00000111 = 00000101
(x & ~(~0 << n)) << (8-n) = 10100000
x >> n = 00001010
(x >> n) | (x & ~(~0 << n) << (8-n)) = 00001010 | 10100000 = 10101010 or 170 in decimal
*/

unsigned rightrot(unsigned x, int n)
{
    if (n > 8)
    {
        n = n % 8;
    }

    return (x >> n) | ((x & ~(~0 << n)) << (8-n));
}
