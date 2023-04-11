#include <stdio.h>
#include <string.h>

char *encodeA(char *str)
{
    int i = 0;
    while (*(str + i))
    {
        if ('a' <= *(str + i) && *(str + i) <= 'z')
            *(str + i) -= 32;
        else if ('A' <= *(str + i) && *(str + i) <= 'Z')
            *(str + i) += 32;
        i++;
    }
    return str;
}

char *decodeA(char *str)
{
    return encodeA(str);
}