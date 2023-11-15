/**
 *interpreter - function
 *@val: var
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include <sys/types.h>
#include <sys/wait.h>

void interpreter(const char *val)
{
	if (access(val, X_OK) == 0)
	{
		if (fork() == 0)
		{
			execl(val, val, (char *)NULL);
			perror(val);
			exit(1);
		}
		else
		{
			wait(NULL);
		}
	}
	else
	{
		fprintf(stderr, "%s: No such file or directory\n", val);
	}
}
int main()
{
	char command[100];

	while (1)
	{
		printf("Enter a command: ");
		if (scanf("%s", command) == 1)
		{
			interpreter(command);
		}
		else
		{
			printf("Invalid command input.\n");
		}
	}

	return 0;
}