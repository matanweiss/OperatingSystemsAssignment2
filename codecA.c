#include <stdio.h>
#include <string.h>

char *encode(char *str)
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

char *decode(char *str)
{
    return encode(str);
}

// int main(int argc, char *argv[])
// {
//     if (argc < 2)
//         return 1;
//     char *b = encode(argv[1]);
//     printf("%s\n", b);
// }