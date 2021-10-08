#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int fd;
	fd = open("lol", O_RDONLY);
	char buf[3];
	int nread;

	buf[2] = -42;
	nread = read(fd, buf, 3);
	printf("%d %d\n", nread,  buf[2]);
	return (0);
}
