#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
 * run_shell - .....
 */
#define MAX_INPUT_SIZE 1024

void run_shell(void)
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		printf("simple_shell$ ");
		fflush(stdout);
		if (!fgets(input, MAX_INPUT_SIZE, stdin))
			break;
		input[strcspn(input, "\n")] = '\0';
		pid_t pid = fork();

		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
			execlp(input, input, (char *)NULL);
		else
		{
			int status;

			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				printf("Exit status: %d\n", WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				printf("Terminated by signal %d\n", WTERMSIG(status));
		}
	}
}
