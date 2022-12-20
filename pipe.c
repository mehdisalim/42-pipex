#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main()
{
	int child;
	int fd[2];

	pipe(fd);
	if ((child = fork()) == -1)
	{
		printf("Error : fork doesnt work\n");
		exit(0);	
	}
	if (child == 0)
	{
		write(fd[1], "hello", 5);
		printf("print from child ");
		exit(0);
	}
	char	str[5];
	read(fd[0], str, 5);
	printf("test : %s\n", str);
}
