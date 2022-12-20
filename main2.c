#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
//	int fd = open ("test", O_RDONLY);
	char	*str = strerror(errno);
	printf("%s\n", str);
}
