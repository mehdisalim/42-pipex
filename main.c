#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

char	*cmd1[] = {"/bin/sh", "-c", "ls -al", 0};
char	*cmd2[] = {"/bin/sh", "grep .", 0};

void	child_process(int fds[2])
{
	dup2(fds[1], 1);
	execve(cmd1[1], cmd1, 0);
	char	*str = malloc(100);
	//read(0, str, 100);
	write(1, str, 100);
}

void	parent_process(int fds[2])
{
	wait(0);
	close(fds[1]);
	dup2(fds[0], 0);
	char	*str = malloc(100);
	read(fds[0], str, 100);
	printf("%s\n", str);
}
int main()
{
	int fds[2];
	if (pipe(fds) == -1)
		perror("pipe :0\n");
	int pid = fork();
	if (pid == -1)
		perror("fork :0\n");
	if (pid == 0)
		child_process(fds);
	else
		parent_process(fds);
	return (0);
}
