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
                    redirection = -2;
            }
            else if (!strcmp(token, ">>"))
            {
                if (doubleRedirection == -1)
                    doubleRedirection = i;
                else
                    doubleRedirection = 2;
            }
            else if (!strcmp(token, "|"))
            {
                if (pipeLine[0] == -1)
                    pipeLine[0] = i;
                else if (pipeLine[1] == -1)
                    pipeLine[1] = i;
                else
                    pipeLine[0] = -2;
            }
            token = strtok(NULL, " ");
            i++;
        }
        argv[i] = NULL;

        /* Is command empty */
        if (argv[0] == NULL)
            continue;

        /* for commands not part of the shell command language */
        if (fork() == 0)
        {
            if (redirection == -2 || doubleRedirection == -2 || pipeLine[0] == -2)
            {
                printf("command not found\n");
                return 1;
            }
            if (redirection != -1 && doubleRedirection != -1)
            {
                printf("command not found\n");
                return 1;
            }
            if (redirection != -1)
            {
                if (freopen(argv[redirection + 1], "w", stdout) == NULL)
                {
                    printf("command not found\n");
                    return 1;
                }
                else
                {
                    argv[redirection] = NULL;
                }
            }
            if (doubleRedirection != -1)
            {
                if (freopen(argv[doubleRedirection + 1], "a", stdout) == NULL)
                {
                    printf("command not found\n");
                    return 1;
                }
                else
                {
                    argv[doubleRedirection] = NULL;
                }
            }
            if (execvp(argv[0], argv) == -1)
            {
                printf("%s: command not found\n", argv[0]);
                return 1;
            }
        }
        wait(NULL);
    }
}
