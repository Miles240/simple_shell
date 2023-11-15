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
char *token;
                char *args[100];

                int i = 0;
                
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

                token = strtok(buffer, " ");

                while (token != NULL)
                {
                    args[i++] = token;
                    token = strtok(NULL, " ");
                }

                args[i] = NULL;

                if (execvp(args[0], args) == -1)
                {
	perror(program_name);
                    exit(EXIT_FAILURE);
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
