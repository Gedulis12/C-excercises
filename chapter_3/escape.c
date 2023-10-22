#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE 8096
int escape(char *t, char *s);

int main()
{
    int c;
    int cc = 0;
    char s[MAX_STR_SIZE];
    char escaped[MAX_STR_SIZE];

    while((c = getchar()) != EOF)
    {
       s[cc] = c;
       cc++;
    }
    s[cc] = '\0';

    escape(s, escaped);
    printf("%s", escaped);
}

int escape(char *t, char *s)
{
    int offset = 0;

    for (int i = 0; i < strlen(t); i++)
    {
        switch (t[i])
        {
            case '\n':
                s[i + offset] = '\\';
                s[i + offset + 1] = 'n';
                offset ++;
                break;
            case '\t':
                s[i + offset] = '\\';
                s[i + offset + 1] = 't';
                offset ++;
                break;
            default:
                s[i + offset] = t[i];
                break;
        }
    }
    s[offset + strlen(t)] = '\0';
    return 0;
}
