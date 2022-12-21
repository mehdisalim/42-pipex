#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>

int	main()
{
	int a = access("test", W_OK);
	if (a == -1)
		printf("the file doesn't have the permission !!");
	else
		printf("can read or write (from || in) this file %d\n", a);
}
