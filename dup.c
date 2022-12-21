#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	int fd = open("test", O_RDONLY | O_WRONLY);
	int fd2 = open("file", O_RDONLY | O_APPEND);
	printf("fd ==> %d\nfd2 ==> %d\n", fd, fd2);
	dup2(1, fd);
	char	*str = malloc(16);
	write(fd, "hello salim", 11);
//	printf("fd ==> %d\nstr ==> %s\n", fd, str);
}
