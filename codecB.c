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

// int main(int argc, char *argv[])
// {
//     if (argc < 2)
//         return 1;
//     char *b = encode(argv[1]);
//     printf("%s\n", b);
//     char *c = decode(b);
//     printf("%s\n", c);
// }