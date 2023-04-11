#include <stdio.h>
#include <string.h>
#include "codec.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("usage: ./encode <codecA/codecB> <string>\n");
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
        printf("usage: ./encode <codecA/codecB> <string>\n");
        return 1;
    }
    printf("%s\n", result);
    // char *b = encode(argv[1]);
    // printf("%s\n", b);
    // printf("%s\n", argv[1]);
    return 0;
}