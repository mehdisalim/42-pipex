#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

/*
void	child_process(int fd[])
{
	
}

char	*readfile(char	*filename)
{
	int fd = 
}
*/

int	main(int ac, char	**av)
{
	int child;
	int fd[2];

	pipe(fd);
	if ((child = fork()) == -1)
	{
		printf("Error : fork doesnt work\n");
		exit(0);	
	}
	char	*str = malloc(10);
	if (child == 0)
	{
		int fd1 = open("test", O_RDONLY, 0777);
		if (fd1 == -1)
			printf("error \n");
		dup2(fd[0], fd1);
		read(fd[0], str, 10);
		printf("print from child %s\n", str);
		exit(0);
	}
	dup2(fd[1], 1);
	write(fd[1], str, 10);
}
