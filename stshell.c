#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"

void sig_handler(int signo)
{
    if (signo == SIGINT)
        printf("child process terminated\n");
}

int main()
{
    int i;
    char *argv[10];
    char command[1024];
    char *token;

    while (1)
    {
        int redirection = -1;
        int doubleRedirection = -1;
        int pipeLine[2] = {-1, -1};
        if (signal(SIGINT, sig_handler) == SIG_ERR)
            printf("\ncan't catch SIGINT\n");
        printf("stshell: ");
        fgets(command, 1024, stdin);
        command[strlen(command) - 1] = '\0'; // replace \n with \0

        if (!strcmp(command, "exit"))
            return 0;

        /* parse command line */
        int failed = 0;
        i = 0;
        token = strtok(command, " ");
        while (token != NULL)
        {
            argv[i] = token;

            // checking redirection:
            if (!strcmp(token, ">"))
            {
                if (redirection == -1)
                    redirection = i;
                else
                    failed = 1;
                if (doubleRedirection != -1 || pipeLine[0] != -1)
                    failed = 1;
            }
            else if (!strcmp(token, ">>"))
            {
                if (doubleRedirection == -1)
                    doubleRedirection = i;
                else
                    failed = 1;
                if (redirection != -1 || pipeLine[0] != -1)
                    failed = 1;
            }
            else if (!strcmp(token, "|"))
            {
                if (pipeLine[0] == -1)
                    pipeLine[0] = i;
                else if (pipeLine[1] == -1)
                    pipeLine[1] = i;
                else
                    failed = 1;
                if (redirection != -1 || doubleRedirection != -1)
                    failed = 1;
            }
            token = strtok(NULL, " ");
            i++;
        }
        argv[i] = NULL;

        /* Is command empty */
        if (argv[0] == NULL)
            continue;

        if (!strcmp(argv[0], "cmp"))
            argv[0] = "./cmp";

        else if (!strcmp(argv[0], "copy"))
            argv[0] = "./copy";

        else if (!strcmp(argv[0], "encode"))
            argv[0] = "./encode";

        else if (!strcmp(argv[0], "decode"))
            argv[0] = "./decode";

        /* for commands not part of the shell command language */
        if (fork() == 0)
        {
            if (failed)
            {
                printf("command not found\n");
                return 1;
            }
            if (redirection != -1)
            {
                if (freopen(argv[redirection + 1], "w", stdout) == NULL)
                {
                    printf("freopen failed\n");
                    return 1;
                }
                argv[redirection] = NULL;
            }
            if (doubleRedirection != -1)
            {
                if (freopen(argv[doubleRedirection + 1], "a", stdout) == NULL)
                {
                    printf("freopen failed\n");
                    return 1;
                }
                argv[doubleRedirection] = NULL;
            }
            if (pipeLine[0] != -1)
            {
                argv[pipeLine[0]] = NULL;

                // execute the first command
                if (fork() == 0)
                {
                    // redirect stdout into a text file
                    if (freopen("pipeline.txt", "w", stdout) == NULL)
                    {
                        printf("freopen failed\n");
                        return 1;
                    }

                    // execute the first command so its output goes to the file
                    if (execvp(argv[0], argv) == -1)
                    {
                        printf("%s: command not found\n", argv[0]);
                        return 1;
                    }
                }
                wait(NULL);

                // two pipelines
                if (pipeLine[1] != -1)
                {
                    argv[pipeLine[1]] = NULL;

                    if (fork() == 0)
                    {
                        // redirect stdin into a text file
                        if (freopen("pipeline.txt", "r", stdin) == NULL)
                        {
                            printf("freopen failed\n");
                            return 1;
                        }

                        // redirect stdout into a text file
                        if (freopen("pipeline2.txt", "w", stdout) == NULL)
                        {
                            printf("freopen failed\n");
                            return 1;
                        }

                        // execute the second command so its input is from the file
                        if (execvp(argv[pipeLine[0] + 1], argv + pipeLine[0] + 1) == -1)
                        {
                            printf("%s: command not found\n", argv[0]);
                            return 1;
                        }
                    }
                    wait(NULL);

                    // redirect stdin into a text file
                    if (freopen("pipeline2.txt", "r", stdin) == NULL)
                    {
                        printf("freopen failed\n");
                        return 1;
                    }

                    // execute the third command so its input is from the file
                    if (execvp(argv[pipeLine[1] + 1], argv + pipeLine[1] + 1) == -1)
                    {
                        printf("%s: command not found\n", argv[0]);
                        return 1;
                    }
                }

                // one pipeline
                else
                {
                    // redirect stdin into a text file
                    if (freopen("pipeline.txt", "r", stdin) == NULL)
                    {
                        printf("freopen failed\n");
                        return 1;
                    }

                    // execute the second command so its input is from the file
                    if (execvp(argv[pipeLine[0] + 1], argv + pipeLine[0] + 1) == -1)
                    {
                        printf("%s: command not found\n", argv[0]);
                        return 1;
                    }
                }
            }
            else if (execvp(argv[0], argv) == -1)
            {
                printf("%s: command not found\n", argv[0]);
                return 1;
            }
        }
        wait(NULL);
    }
}
