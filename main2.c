#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <strings.h>

static void commandline(const char *command)
{
	int	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		char *str = malloc(100);
		char *argemments[] = {"/bin/sh", "-c", (char *)command, NULL};
		execve(argemments[0], argemments, 0);
		read(0, str, 100);
		printf("\n#%s#\n", str);
		exit(0);
	}
	wait(0);
}

int main()
{
	char	*command = malloc(50);
	while (1)
	{
		write(1, "\033[0;32mroot $ => \033[0m", 21);
		read(0, command, 50);
		if (!strncmp(command, "exit", 4) || !strncmp(command, "quit", 4))
			break ;
		commandline(command);
		bzero(command, 50);
	}
}
