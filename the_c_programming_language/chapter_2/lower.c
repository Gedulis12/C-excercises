#include <stdio.h>

int main()
{
    int c;
    while((c = getchar()) != EOF)
    {
        printf("%c", (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c);
    }
}
