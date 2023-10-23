#include <stdio.h>
#define MAXLINE 1000
#define IN  1
#define OUT 0
#define FOLD_AT 30
#define FORCE_FOLD_AT 70

int get_line(char line[], int maxline);
void foldline(char longline[], char foldedline[]);

int main()
{
    int len;
    char line[MAXLINE];
    char foldedline[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0)
    {
        if (len > 0)
        {
            foldline(line, foldedline);
            printf("%s", foldedline);
        }
    }
    return 0;
}

int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void foldline(char longline[], char foldedline[])
{
    int i, nc, state, force_fold_count;
    state = OUT;
    nc = 0;
    i = 0;
    force_fold_count = 0;

    while(longline[i] != '\0')
    {
        ++nc;
        if (nc >= FOLD_AT && (longline[i] == ' ' || longline[i] == '\t'))
        {
            foldedline[i] = '\n';
            nc = 0;
        }
        else
        {
            foldedline[i] = longline[i - force_fold_count];
        }

        if (nc >= FORCE_FOLD_AT)
        {
            foldedline[i] = '\n';
            force_fold_count++;
            nc = 0;
        }
        i++;
    }
    foldedline[i] = '\0';
}
