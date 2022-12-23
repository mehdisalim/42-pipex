#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void	child_process(int fds[2])
{
	close(fds[0]);
	dup2(fds[1], 1);
	write(fds[1], "hello world", 12);
}

void	parent_process(int fds[2], char	*infile)
{
	close(fds[1]);
	char *str = malloc(13);
	dup2(fds[0], 0);
	read(fds[0], str, 12);
	char *command[] = {"grep llo test", "<", infile, NULL};
	execve(command[0], command, 0);
	//printf("%s\n", str);
}

int		main(int ac, char	**av)
{
	int fds[2];
	int	pid;

	pipe(fds);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		child_process(fds);
	else
		parent_process(fds, av[1]);
	return (0);
}
