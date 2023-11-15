
/*
 * simple_shell - function
*/
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    char *program_name = "./shell";
	pid_t child_pid;

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

            
            child_pid = fork();

            if (child_pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if (child_pid == 0)
            {
                char **args = malloc(2 * sizeof(char *));
	if (args == NULL)
	{
    	perror("malloc");
    	_exit(EXIT_FAILURE);
	}

	args[0] = buffer;
	args[1] = NULL;

                if (execve(buffer, args, NULL) == -1)
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
