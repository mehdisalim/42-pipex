#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	close(1);
	int fd = open("fd", O_CREAT | O_WRONLY, 0777);
	printf("hello world !! %d\n", fd);

}
