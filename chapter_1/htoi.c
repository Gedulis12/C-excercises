#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HEX_START 2
#define HEX_BASE 16
#define HEX_SIZE 35

int get_hex(char *hex_str);

long htoi(char *hex_str, int hex_str_size);

int main()
{
    char hex_str[HEX_SIZE];
    int nc;
    long number;

    if ((nc = get_hex(hex_str)) != -1)
    {
        number = htoi(hex_str, nc);
    }

    if (number == -1)
    {
        printf("could not convert hex into decimal\n");
        return 1;
    }

    printf("HEX value provided: %s\nNumeric value: %ld\n", hex_str, number);
}

int get_hex(char *hex_str)
{
    int nc = 0;
    int cc;

    while ((cc = getchar()) != EOF && cc != '\n')
    {
        if ((nc == 0 && cc != '0') || ((nc == 1 && cc != 'x') && (nc == 1 && cc != 'X')))
        {
            printf("not a valid hex format\n");
            return -1;
        }
        else if ((nc > 1) && (!(cc >= '0' && cc <= '9') && !(cc >= 'a' && cc <= 'f') && !(cc >= 'A' && cc <= 'F') ))
        {
            printf("character %c is not a valid expected in hex format\n", cc);
            return -1;
        }

        hex_str[nc] = cc;

        if (nc > 30)
        {
            printf("statement too long, up to %d hex characters are supported\n", HEX_SIZE);
            return -1;
        }
        ++nc;
    }
    hex_str[nc] = '\0';
    return nc;
}

long htoi(char *hex_str, int hex_str_size)
{
    long number = 0;
    int base;
    int power;

    power = hex_str_size - 3; // -3 for 0x and null terminator

    for (int i = HEX_START; i < hex_str_size; i++)
    {
        switch (hex_str[i])
        {
            case '0':
                base = 0;
                break;
            case '1':
                base = 1;
                break;
            case '2':
                base = 2;
                break;
            case '3':
                base = 3;
                break;
            case '4':
                base = 4;
                break;
            case '5':
                base = 5;
                break;
            case '6':
                base = 6;
                break;
            case '7':
                base = 7;
                break;
            case '8':
                base = 8;
                break;
            case '9':
                base = 9;
                break;
            case 'a':
                base = 10;
                break;
            case 'A':
                base = 10;
                break;
            case 'b':
                base = 11;
                break;
            case 'B':
                base = 11;
                break;
            case 'c':
                base = 12;
                break;
            case 'C':
                base = 12;
                break;
            case 'd':
                base = 13;
                break;
            case 'D':
                base = 13;
                break;
            case 'e':
                base = 14;
                break;
            case 'E':
                base = 14;
                break;
            case 'f':
                base = 15;
                break;
            case 'F':
                base = 15;
                break;

            default:
                printf("Invalid hex string\n");
                return -1;
        }

        if (power == 0)
        {
            number = number + base;
        }
        else
        {
            number = number + (base * pow(HEX_BASE, power));
        }
        --power;
    }
    return number;
}
