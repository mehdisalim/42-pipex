#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void	redirect_to_file(char	*av[])
{
	char *args[] = {"/bin/bash", "-c", av[2], NULL};
	int fd = open(av[1], O_RDONLY | O_WRONLY);
	dup2(fd, 1);
	execve(args[0], args, NULL);
}

int main(int ac, char **av)
{
	redirect_to_file(av);
}
