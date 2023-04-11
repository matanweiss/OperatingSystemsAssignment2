#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <limits.h>

int compare(char *filename1, char *filename2, int verbose, int ignoreCase)
{
    FILE *file1 = fopen(filename1, "rb");
    FILE *file2 = fopen(filename2, "rb");
    if (!file1 || !file2)
        return 1;
    char char1 = 0;
    char char2 = 0;
    while (char1 == char2 && char1 != EOF && char2 != EOF)
    {
        char1 = fgetc(file1);
        char2 = fgetc(file2);
        if (ignoreCase)
        {
            char1 = tolower(char1);
            char2 = tolower(char2);
        }
    }
    if (char1 != EOF || char2 != EOF)
    {
        if (verbose)
            printf("distinct\n");
        return 1;
    }
    if (verbose)
        printf("equals\n");
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 3 || 5 < argc)
    {
        printf("usage: ./cmp <file1> <file2> -v\n");
        return 1;
    }
    int ignoreCase = 0;
    int verbose = 0;
    if (3 < argc && !strcmp(argv[3], "-v"))
        verbose = 1;
    if (3 < argc && !strcmp(argv[3], "-i"))
        ignoreCase = 1;
    if (4 < argc && !strcmp(argv[4], "-v"))
        verbose = 1;
    if (4 < argc && !strcmp(argv[4], "-i"))
        ignoreCase = 1;
    return compare(argv[1], argv[2], verbose, ignoreCase);
}