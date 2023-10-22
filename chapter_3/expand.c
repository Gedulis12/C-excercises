#include <stdio.h>
#include <string.h>

#define MAX_STR_SIZE 8096

int expand(char *s1, char *s2);

int main()
{
    int c;
    int cc = 0;
    char s1[MAX_STR_SIZE];
    char s2[MAX_STR_SIZE];

    while((c = getchar()) != EOF)
    {
       s1[cc] = c;
       cc++;
    }
    s1[cc] = '\0';

    expand(s1, s2);
    printf("%s", s2);

    return 0;
}

/*
 expands shorthand notations like a-z A-Z 0-9 in the string s1 into the
 equivalent complete list abc...xyz in s2. leading and trailing '-'s are taken literally
 */
int expand(char *s1, char *s2)
{
    int start, end;
    int range;
    int offset = 0;
    int dst_index = 0;

    for (int i = 0; i<strlen(s1); i++)
    {
        start = 0;
        end = 0;
        range = 0;

        if ((s1[i] >= 'A' && s1[i] <= 'Z')
                && s1[i+1] == '-'
                && ((s1[i+2] >= 'A' && s1[i+2] <= 'Z')))
        {
            start = s1[i];
            end = s1[i+2];
        } else if ((s1[i] >= 'a' && s1[i] <= 'z')
                && s1[i+1] == '-'
                && ((s1[i+2] >= 'a' && s1[i+2] <= 'z')))
        {
            start = s1[i];
            end = s1[i+2];
        } else if ((s1[i] >= '0' && s1[i] <= '9')
                && s1[i+1] == '-'
                && ((s1[i+2] >= '0' && s1[i+2] <= '9')))
        {
            start = s1[i];
            end = s1[i+2];
        }

        if (start != 0 && end != 0)
        {
            range = (end - start) + 1;
            for (int j = 0; j < range; j++)
            {
                s2[dst_index + offset + j] = start + j;
            }
            offset += (end - start);
            i += 2;
            dst_index ++;
            continue;
        }

        s2[dst_index + offset] = s1[i];
        dst_index ++;
    }

    s2[offset + strlen(s1)] = '\0';
    return 0;
}
