#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int fd1 = open("file1", O_RDONLY, 0777);
	int fd2 = open("file2", O_RDONLY | O_WRONLY, 0777);
	dup2(fd2, 1);
	dup2(fd1, 0);
	int fds[2] = {fd1, fd2};
	pipe(fds);
	int child = fork();
	if (child == -1)
		exit(1);
	if (child == 0)
	{
		close(fds[0]);
		write(fds[1], "hello world", 11);
		printf("hello from child\n");
	}
	else
	{
		close(fds[1]);
		char	str[11];
		read(fds[0], str, 11);
		printf("test : %s\n", str);
	}
	return (0);
}
