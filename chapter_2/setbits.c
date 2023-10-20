#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned setbitsoneliner(unsigned x, int p, int n, unsigned y);

int main ()
{
    int a = setbits(85, 4, 3, 255);
    int b = setbitsoneliner(85, 4, 3, 255);
    printf("setbits returned: %i \n", a); // should print 93
    printf("setbitsoneliner returned: %i \n", b); // should print 93
}

/*
function that returns x with the n bits that begin at position p set to the most n bits of y, leaving the other bits unchanged.
*/
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    // get the n rightmost bits of y
    y = (y >> (p+1-n)) & ~(~0 << n);
    /*
    y = 11111111
    y >> (4+1-3) = 00111111
    ~(~0 << 3)   = 00000111
    00111111 & 00000111 = 00000111
     */

    // leftshift the y by the p+1-n bits
    y = y << (p+1-n);
    /*
    y = 00000111
    y << (p+1-n) = 00011100
    */

    // create a mask and poke a hole of size n in x at starting position p
    x & ~(~(~0 << n) << (p+1-n));
    /*
    x = 01010101
    ~0 = 11111111
    ~0 << n = 11111000
    ~(~0 << n) = 00000111
    ~(~0 << n) << (p+1-n) = 00011100
    ~(~(~0 << n) << (p+1-n)) = 11100011
    x & ~(~(~0 << n) << (p+1-n)) = 01000001
     *
    */

    // apply the y bits on x with bitwise OR
    x = x | y;
    /*
    x | y = 01000001 | 00011100 = 01011101 or 93 in decimal
    */
    return x;
}


unsigned setbitsoneliner(unsigned x, int p, int n, unsigned y)
{
    return x & ~(~(~0 << n) << (p+1-n)) | (y >> (p+1-n)) & ~(~0 << n) << (p+1-n);
}
