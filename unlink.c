#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	int fd = open("test", O_RDONLY);
	int a = unlink("test/test");
	char *str = malloc(13);
	read(fd, str, 12);
	printf("a ==> %d\nstr ==> %s\nfd ==> %d\n", a, str, fd);
}
