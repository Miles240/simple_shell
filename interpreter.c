#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include <sys/types.h>
#include <sys/wait.h>

/**
 *interpreter - function
 *@val: var
 *
 */

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
