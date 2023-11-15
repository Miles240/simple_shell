#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#define BUFFER_SIZE 1024

void simple_shell(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    char *program_name = "./shell"; // Change this to your program name

    while (1)
    {
        write(STDOUT_FILENO, "#cisfun$ ", 9);
        if (getline(&buffer, &bufsize, stdin) == -1)
        {
            if (feof(stdin))
            {
                write(STDOUT_FILENO, "\n", 1);
                free(buffer);
                exit(EXIT_SUCCESS);
            }
            perror("getline");
            exit(EXIT_FAILURE);
        }
        if (buffer[0] != '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
            pid_t child_pid = fork();
            if (child_pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (child_pid == 0)
            {
                if (execve(buffer, (char *[]){buffer, NULL}, NULL) == -1)
                {
                    perror(program_name);
                    _exit(EXIT_FAILURE);
                }
            }
            else
            {
                waitpid(child_pid, NULL, 0);
            }
        }
    }

    free(buffer);
}
