#include <stdio.h>
#define MAXLINE 1000
int get_line(char line[], int maxline);

int main()
{
    int len;
    char line[MAXLINE];
    char longest[MAXLINE];

    while ((len = get_line(line, MAXLINE)) >= 0)
    {
        if (len > 0)
        {
            printf("%s", line);
        }
    }
    return 0;
}

int get_line(char s[], int lim)
{
    int c, i, tab_count, d;
    tab_count = 0;
    int space_count = 0;
    int spaces_per_tab = 4;
    d = 0;
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
    {
        if (i == tab_count && c == '\t')
        {
            ++tab_count;
        }
        else
        {
            space_count = tab_count * spaces_per_tab;
            s[space_count + d] = c;
            ++d;
        }
    }
    for (i = 0; i < space_count; i++)
    {
        s[i] = ' ';
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
