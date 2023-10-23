#include <stdio.h>
#define MAXLINE 1000
int get_line(char line[], int maxline);
int reverse_line(char line[], char reversed_line[]);

int main()
{
    int len;
    char line[MAXLINE];
    char reversed_line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) >= 0)
    {
        if (len > 0)
        {
            reverse_line(line, reversed_line);
            printf("%s", reversed_line);
        }
    }
    printf("\n");
    return 0;
}

int get_line(char s[], int lim)
{
    int c, i, b, d;
    b = 0;
    d = 0;
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
    {
        if (i == b && (c == ' ' || c == '\t'))
        {
            ++b;
        }
        else
        {
            s[d] = c;
            ++d;
        }
    }
    if (c == '\n')
    {
        s[d] = c;
    }
    if (c == EOF)
    {
        return -1;
    }
    s[d+1] = '\0';

    return d;
}


int reverse_line(char line[], char reversed_line[])
{

    int i, j;
    for (i = 0; line[i] != '\0'; i++)
        ;
    i = i - 1;
    for (j = 0; j <= i; j++)
    {
        reversed_line[j] = line[i - j];
    }
        reversed_line[j] = '\0';
    return 0;
}
