#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void	child_process(int pfd[2], char **av)
{
	char *command[] = {"/bin/bash", "-c", av[2], 0};
	close(pfd[0]);
	int fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit(0);
	dup2(fd, STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	execve(command[0], command, 0);
	close(fd);
	exit(0);
}

void	parent_process(int pfd[2], char	**av)
{
	char	*command[] = {"/bin/bash", "-c", av[3], NULL};
	close(pfd[1]);
//	close(STDOUT_FILENO);
	int fd = open(av[4], O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
	{
		printf("fd is equal -1");
		exit(0);
	}
//	dup(fd);
	dup2(pfd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	execve(command[0], command, 0);
	close(fd);
}

int	main(int ac, char *av[])
{
	(void) ac;
	int pfd[2];
	pipe(pfd);

	int pid = fork();
	if (pid == 0)
		child_process(pfd, av);
	wait(NULL);
	parent_process(pfd, av);
	while(1);
}
