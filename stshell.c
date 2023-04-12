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
            if (execvp(argv[0], argv) == -1)
            {
                printf("command not found\n");
                return 1;
            }
        }
        wait(NULL);
    }
}
