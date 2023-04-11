#include <stdio.h>
#include <string.h>
#include "codec.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage : encode <codec> <message>\n");
        return 1;
    }
    char *result;
    if (!strcmp(argv[1], "codecA"))
    {
        result = encodeA(argv[2]);
    }
    else if (!strcmp(argv[1], "codecB"))
    {
        result = encodeB(argv[2]);
    }
    else
    {
        printf("Usage : encode <codec> <message>\n");
        return 1;
    }
    printf("%s\n", result);
    return 0;
}