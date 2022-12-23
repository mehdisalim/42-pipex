#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int fds[2];
	pipe(fds);
	int pid;
	int pid2;
	if ((pid = fork()) == -1) // if there is an error happens
		return (1);
	if (pid == 0) // first child
	{
		close(fds[0]); //close unused fd (stdin)
		dup2(fds[1], STDOUT_FILENO); // .....
		execlp(av[1], av[1], 0); // execve to run the command
	}
	if ((pid2 = fork()) == -1) 
		return (1);
	if (pid2 == 0) // second child
	{
		close(fds[1]); // close unused fd
		dup2(fds[0], STDIN_FILENO);
		execlp(av[2], av[2], 0);
	}
	close(fds[0]);
	close(fds[1]);

	wait(0);
	wait(0);
}
