#include <stdio.h>

int get_string(char *string);
int any(char *string, char *search);

int main(int argc, char *argv[])
{
    char string[10000] = {0};
    char *search = argv[1];
    int position;
    if (argc != 2)
    {
        printf("Error: exactly one argument must be provided\n");
        return 1;
    }

    if (get_string(string) > 0)
    {
        position = any(string, search);
    }

    if (position != -1)
    {
        printf("found at position %d\n", position);
        return 0;
    }
    printf("no match was found\n");
    return 0;
}

int get_string(char *string)
{
    int c;
    int nc = 0;
    while ((c = getchar()) != EOF)
    {
        string[nc] = c;
        ++nc;
    }
    string[nc] = '\0';
    return nc;
}

int any(char *string, char *search)
{
    int i = 0;
    int j = 0;
    while (string[i] != '\0')
    {
        j = 0;
        while (search[j] != '\0')
        {
            if (string[i] == search[j])
            {
                return i;
            }
            j++;
        }
        i++;
    }
    return -1;
}
