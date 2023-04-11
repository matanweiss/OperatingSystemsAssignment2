#include <stdio.h>
#include <string.h>

char *encodeB(char *str)
{
    int i = 0;
    while (*(str + i))
    {
        *(str + i) += 3;
        i++;
    }
    return str;
}

char *decodeB(char *str)
{
    int i = 0;
    while (*(str + i))
    {
        *(str + i) -= 3;
        i++;
    }
    return str;
}