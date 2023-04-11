#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int copy(char *filename1, char *filename2, int verbose, int force)
{
    FILE *file1 = fopen(filename1, "rb");
    if (!force && access(filename2, F_OK) == 0)
    {
        if (verbose)
            printf("target file exist\n");
        return 1;
    }
    FILE *file2 = fopen(filename2, "wb");
    if (!file1 || !file2)
    {
        if (verbose)
            printf("general failure\n");
        return 1;
    }
    char c = fgetc(file1);
    while (c != EOF)
    {
        putc(c, file2);
        c = fgetc(file1);
    }
    if (verbose)
        printf("success\n");
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 3 || 5 < argc)
    {
        printf("usage: ./copy <file1> <file2> [-v] [-f]\n");
        return 1;
    }
    int force = 0;
    int verbose = 0;
    if (3 < argc && !strcmp(argv[3], "-v"))
        verbose = 1;
    if (3 < argc && !strcmp(argv[3], "-f"))
        force = 1;
    if (3 < argc && !verbose && !force)
    {
        printf("hi usage: ./copy <file1> <file2> [-v] [-f]\n");
        return 1;
    }
    if (4 < argc && !strcmp(argv[4], "-v"))
        verbose = 1;
    if (4 < argc && !strcmp(argv[4], "-f"))
        force = 1;
    if (4 < argc && (!verbose || !force))
    {
        printf("usage: ./copy <file1> <file2> [-v] [-f]\n");
        return 1;
    }
    return copy(argv[1], argv[2], verbose, force);
}