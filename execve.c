#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char	**av)
{
	char	*args[] = {"/bin/sh", "-c", av[1], NULL};
	execve(args[0], args, NULL);
}
