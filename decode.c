#include <stdio.h>
#include <string.h>
#include "codec.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage : decode <codec> <message>\n");
        return 1;
    }
    char *result;
    if (!strcmp(argv[1], "codecA"))
    {
        result = decodeA(argv[2]);
    }
    else if (!strcmp(argv[1], "codecB"))
    {
        result = decodeB(argv[2]);
    }
    else
    {
        printf("Usage : decode <codec> <message>\n");
        return 1;
    }
    printf("%s\n", result);
    return 0;
}